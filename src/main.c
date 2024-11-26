#include "minishell.h"

int	minishell(t_shell *shell, t_token **tokens, char **envp)
{
	t_ast	**ast;

	write(1, "DEBUG\n", 6);
	if (!get_env_and_export(envp, shell))
		return (0);
	ast = (t_ast **)malloc(sizeof(t_ast));
	if (!ast)
		return (0);
	while (1)
		minishell_loop(shell, tokens, ast);
	free_envp(envp);
}

int	minishell_loop(t_shell *shell, t_token **tokens, t_ast **ast)
{
	char **mtr;

	shell->line = readline("minishell$ ");
	if (!shell->line)
		return (free(tokens), free(ast), printf("exit\n"), 0);
	if (shell->line)
		add_history(shell->line);
	mtr = mini_split(shell->line);
	create_token(mtr, tokens);
	lexer(tokens);
	create_ast(tokens, ast);
	executor(tokens, shell);
	free_mtr(mtr);
	free(shell->line);
	free_token(tokens);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	**tokens;
	t_shell	shell;

	(void)argc;
	(void)argv;
	tokens = (t_token **)malloc(sizeof(t_token));
	if (!tokens)
		return (-1);
	minishell( &shell, tokens, envp);
	return (0);
}

bool get_env_and_export(char **envp, t_shell *shell)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * (i + 1));
	shell->export = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shell->env || !shell->export)
		return (false);
	i = -1;
	while (envp[++i])
		shell->env[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
	write(1, "DEBUG\n", 6);
	i = -1;
	while (envp[++i])
		shell->export[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
	return (true);
}
