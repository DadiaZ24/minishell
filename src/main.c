#include "minishell.h"

int	minishell(t_shell *shell, t_token **tokens, char **envp)
{
	(void)envp;
	(void)tokens;
	int	i;

	i = 0;
	while (1)
	{
		shell->line = readline("minishell$ ");
		if (!shell->line)
			return (printf("error reading line"), 0);
		if (shell->line)
			add_history(shell->line);
		i = ft_words(shell->line);
		printf("WC == [%d]\n", i);
		printf("LINE == [%s]\n", shell->line);
		pwd();
		free (shell->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token	**tokens;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	tokens = (t_token **)malloc(sizeof(t_token));
	if (!tokens)
		return (-1);
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (-1);
	minishell(shell, tokens, envp);
	//free_tokens(tokens);
	printf("\n\nSAI!!!!\n\n");
	return (0);
}
