#include "minishell.h"

char **get_token(t_token *token, t_cmds *cmd)
{
    int size = 0;
    char **args = NULL;
    t_token *temp = token;
	(void)cmd;
    while (token)
    {
        if (token->type == RED_IN || token->type == HERE_DOC ||
            token->type == APPEND || token->type == RED_OUT)
            token = token->next->next;
        else if (token->type == PIPE)
            break;
        if (token && token->type == ARG && (token->info[0] != '\0' || token->d_quotes))
            size++;
        if (token)
            token = token->next;
    }

    if (size == 0)
        return NULL;

    // Allocate memory for args array
    args = (char **)malloc(sizeof(char *) * (size + 1));
    if (!args)
        return NULL;

    int i = 0;
    while (temp)
    {
        if (temp->type == PIPE)
            break;

        if (temp->type == RED_IN || temp->type == HERE_DOC ||
            temp->type == APPEND || temp->type == RED_OUT)
            temp = temp->next;
        else if (temp->type == ARG && (temp->info[0] != '\0' || temp->d_quotes) && (!temp->prev || (temp->prev->type != RED_IN &&
                                                      temp->prev->type != RED_OUT &&
                                                      temp->prev->type != APPEND &&
                                                      temp->prev->type != HERE_DOC)))
            args[i++] = ft_strdup(temp->info);

        temp = temp->next;
    }

    args[i] = NULL;
    return args;
}

t_token *get_redir(t_token *token)
{
    t_token *redir = (t_token *)malloc(sizeof(t_token));

    redir = (t_token *)malloc(sizeof(t_token));
    if (!redir)
        return NULL;
    redir->type = token->type;
    redir->info = token->next->info;
    redir->next = NULL;
    return (redir);
}

void init_cmds(t_cmds **cmds)
{
    if (!cmds)
        return;

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

void add_redirection(t_cmds *cmd, t_token *token)
{
    t_token *redir = get_redir(token);

    redir = get_redir(token);
    if (!redir)
        return;
    if (cmd->redir)
    {
        t_token *temp = cmd->redir;
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

void ft_div(t_cmds **cmds, t_token *token)
{
    t_token *temp;
    t_token *begin;
    t_cmds *cmd;
    
    if (!cmds || !*cmds || !token)
        return;
    cmd = *cmds;
    begin = NULL;
    temp = NULL;
    if (token->d_quotes)
        cmd->d_quotes = true;
    cmd->args = get_token(token, cmd);
    if (cmd->args && cmd->args[0] && !cmd->cmd)
        cmd->cmd = ft_strdup(cmd->args[0]);
    while (token && token->type != PIPE)
    {
        if (token->type == RED_IN || token->type == RED_OUT ||
            token->type == APPEND || token->type == HERE_DOC)
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

t_cmds **ft_cmd_div(t_token *token, t_executor *exec)
{
/* 	t_cmds	*test;
	t_token	*re_test;
	int		i; */
    if (!token)
        return NULL;
    *exec->cmds = NULL;
    init_cmds(exec->cmds);
    t_cmds *current_cmd = *exec->cmds;

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

	/*#############################*/
/*         test = *exec->cmds;
        while (test)
        {
            re_test = test->redir;
            while (re_test)
            {
                re_test = re_test->next;
            }
            test = test->next;
        } */
	/*#############################*/
    return (exec->cmds);
}
