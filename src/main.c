#include "minishell.h"

int	minishell(t_shell *shell, t_token **tokens, char **envp)
{
	(void)envp;
	(void)tokens;
	char	**mtr;

	mtr = NULL;
	while (1)
	{
		shell->line = readline("minishell$ ");
		if (!shell->line)
			return (printf("error reading line"), 0);
		if (shell->line)
			add_history(shell->line);
		mtr = mini_split(shell->line);
		ft_putmtr(mtr);
		printf("LINE == [%s]\n", shell->line);
		//pwd();
		free (shell->line);
	}
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
	//free_tokens(tokens);
	return (0);
}

