#include "minishell.h"

int	executor_execve(char **line, char **split, char **envp)
{
	if (execve(split[0], line, envp) == -1)
		return (perror("ERRO NO EXECVE FDP!!!!!"), 0);
	return (0);
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
	minishell(tokens, &shell, envp);
	//free_tokens(tokens);
	return (0);
}

int	minishell(t_token **tokens, t_shell *shell, char **envp)
{
	char *line;
	(void)envp;
	(void)tokens;

	*tokens = malloc(sizeof(t_token));
	if (!*tokens)
		return (0);
	printf("%s", (*tokens)->info);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (printf("error reading line"), 0);
		if (line)
			add_history(line);
		//SPLIT TOKENS;;;
		if ((*tokens)->type == CMD_BIN || (*tokens)->type == CMD_EVE)
			executor(tokens, shell);
	}
}
