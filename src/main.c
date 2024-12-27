#include "minishell.h"

int minishell(t_executor *exec, char **envp)
{
	if (!get_env(envp, exec->shell))
		return (0);
	exec->cmds = (t_cmds **)malloc(sizeof(t_cmds));
	if (!exec->cmds)
		return (0);
	while (minishell_loop(exec, exec->token))
		;
	return (0);
}

int minishell_loop(t_executor *exec, t_token **tokens)
{
	char **mtr;

	exec->shell->line = readline("minishell$ ");
	if (!exec->shell->line)
		return (free_d(exec), printf("exit\n"), 0);
	if (exec->shell->line)
		add_history(exec->shell->line);
	if (!exec->shell->line[0])
		return (free(exec->shell->line), 1);
	mtr = mini_split(exec->shell->line);
	create_token(mtr, tokens);
	free_mtr(mtr);
	if (!syntax_checker(tokens))
		return (free_token(*tokens), 1);
	lexer(tokens);
	expander(tokens, exec);
	//ft_print_token(tokens);
	ft_cmd_div(*tokens, exec);
	free_token(*tokens);
	executor(exec);
	dup2(exec->fd_out, STDOUT_FILENO);
	wait_pid(exec);
	free_all(exec);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_executor *exec;

	(void)argc;
	(void)argv;
	exec = (t_executor *)malloc(sizeof(t_executor));
	if (!exec)
		return (-1);
	exec = init_exec(exec);
	if (!exec)
		return (-1);
	minishell(exec, envp);
	return (0);
}
