#include "minishell.h"

char **get_token(t_token *token, t_cmds *cmd)
{
    int size = 0;
    char **args = NULL;
    t_token *temp = token;
	(void)cmd;
    // Calculate the size of the args array
    while (token)
    {
        if (token->type == RED_IN || token->type == HERE_DOC ||
            token->type == APPEND || token->type == RED_OUT)
            token = token->next->next;
        else if (token->type == PIPE)
            break;
        if (token && token->type == ARG)
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
        else if (temp->type == ARG && (!temp->prev || (temp->prev->type != RED_IN &&
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
    if (!token)
        return NULL;

    t_token *redir = (t_token *)malloc(sizeof(t_token));
    if (!redir)
        return NULL;

    redir->type = token->type;
    redir->info = token->next ? token->next->info : NULL;
    redir->next = NULL;

    return redir;
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
    }
}

void add_redirection(t_cmds *cmd, t_token *token)
{
    t_token *redir = get_redir(token);

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
        cmd->redir = redir;
}

void ft_div(t_cmds **cmds, t_token *token)
{
    if (!cmds || !*cmds || !token)
        return;

    t_cmds *cmd = *cmds;
    cmd->args = get_token(token, cmd);

    if (cmd->args && cmd->args[0] && !cmd->cmd)
        cmd->cmd = ft_strdup(cmd->args[0]);

    while (token && token->type != PIPE)
    {
        if (token->type == RED_IN || token->type == RED_OUT ||
            token->type == APPEND || token->type == HERE_DOC)
        {
            add_redirection(cmd, token);
            token = token->next ? token->next->next : NULL;
        }
        else if (token->type == ARG)
        {
            while (token && token->type == ARG)
                token = token->next;
        }
    }
}

t_cmds **ft_cmd_div(t_token *token, t_executor *exec)
{
	t_cmds	*test;
	t_token	*re_test;
	int		i;
    exec->cmds = (t_cmds **)malloc(sizeof(t_cmds));
    if (!exec->cmds)
        return NULL;
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
	test = *exec->cmds;
	while (test)
	{
		i = 0;
		re_test = test->redir;
		printf("=====================================================\n");
		printf("process cmd: %s\n", test->cmd);
		while (test->args && test->args[i])
			printf("process args: %s\n", test->args[i++]);
		i = 0;
		while (re_test)
		{
			printf("process redir: type-> %d, file-> %s\n", re_test->type,
					re_test->info);
			re_test = re_test->next;
		}
		printf("=====================================================\n");
		test = test->next;
	}
	/*#############################*/
    return (exec->cmds);
}