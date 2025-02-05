#include "minishell.h"

char	**get_token(t_token *token)
{
	int		size;
	int		i;
	char	**args;
	t_token	*temp;

	size = 0;
	args = NULL;
	temp = token;
	i = 0;
	while (token)
	{
		if (token->type == RED_IN || token->type == HERE_DOC
			|| token->type == APPEND || token->type == RED_OUT)
			token = token->next->next;
		else if (token->type == PIPE)
			break ;
		if (token && token->type == ARG && (token->info[0] != '\0'
				|| token->d_quotes))
			size++;
		if (token)
			token = token->next;
	}
	if (size == 0)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (temp)
	{
		if (temp->type == PIPE)
			break ;
		if (temp->type == RED_IN || temp->type == HERE_DOC
			|| temp->type == APPEND || temp->type == RED_OUT)
			temp = temp->next;
		else if (temp->type == ARG && (temp->info[0] != '\0' || temp->d_quotes)
			&& (!temp->prev || (temp->prev->type != RED_IN
					&& temp->prev->type != RED_OUT && temp->prev->type != APPEND
					&& temp->prev->type != HERE_DOC)))
			args[i++] = ft_strdup(temp->info);
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

t_token	*get_redir(t_token *token)
{
	t_token	*redir;

	redir = (t_token *)malloc(sizeof(t_token));
	if (!redir)
		return (NULL);
	redir->type = token->type;
	redir->info = token->next->info;
	redir->next = NULL;
	return (redir);
}

void	init_cmds(t_cmds **cmds)
{
	if (!cmds)
		return ;
	*cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (*cmds)
	{
		(*cmds)->cmd = NULL;
		(*cmds)->args = NULL;
		(*cmds)->redir = NULL;
		(*cmds)->next = NULL;
		(*cmds)->d_quotes = false;
		(*cmds)->fd_hd = -1;
	}
}

void	add_redirection(t_cmds *cmd, t_token *token)
{
	t_token	*redir;
	t_token	*temp;

	redir = get_redir(token);
	if (!redir)
		return ;
	if (cmd->redir)
	{
		temp = cmd->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = redir;
	}
	else
	{
		cmd->redir->info = ft_strdup(redir->info);
		cmd->redir->type = redir->type;
		free(redir);
	}
}

void	ft_div(t_cmds **cmds, t_token *token)
{
	t_token	*temp;
	t_token	*begin;
	t_cmds	*cmd;

	if (!cmds || !*cmds || !token)
		return ;
	cmd = *cmds;
	begin = NULL;
	temp = NULL;
	if (token->d_quotes)
		cmd->d_quotes = true;
	cmd->args = get_token(token);
	if (cmd->args && cmd->args[0] && !cmd->cmd)
		cmd->cmd = ft_strdup(cmd->args[0]);
	while (token && token->type != PIPE)
	{
		if (token->type == RED_IN || token->type == RED_OUT
			|| token->type == APPEND || token->type == HERE_DOC)
		{
			if (!temp)
			{
				begin = (t_token *)malloc(sizeof(t_token));
				begin->type = token->type;
				begin->info = ft_strdup(token->next->info);
				token = token->next;
				begin->next = NULL;
				cmd->redir = begin;
				temp = begin;
			}
			else
			{
				temp->next = (t_token *)malloc(sizeof(t_token));
				temp = temp->next;
				temp->type = token->type;
				temp->info = ft_strdup(token->next->info);
				token = token->next;
				temp->next = NULL;
			}
		}
		else
			token = token->next;
	}
	cmd->redir = (*cmds)->redir;
}

t_cmds	**ft_cmd_div(t_token *token, t_executor *exec)
{
	t_cmds	*current_cmd;

	if (!token)
		return (NULL);
	*exec->cmds = NULL;
	init_cmds(exec->cmds);
	current_cmd = *exec->cmds;
	while (token)
	{
		ft_div(&current_cmd, token);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
		{
			init_cmds(&current_cmd->next);
			current_cmd = current_cmd->next;
			token = token->next;
		}
	}
	return (exec->cmds);
}
