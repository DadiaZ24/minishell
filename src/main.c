#include "minishell.h"

int	minishell(t_shell *shell, t_token **tokens, char **envp)
{
	(void)envp;
	char	**mtr;
	int		i;

	mtr = NULL;
	i = 0;
	while (1)
	{
		shell->line = readline("minishell$ ");
		if (!shell->line)
			return (printf("error reading line"), 0);
		if (shell->line)
			add_history(shell->line);
		mtr = mini_split(shell->line);
		create_token(mtr, tokens);
		lexer(tokens, false);
		ft_print_token(tokens);
		/* i = mini_words(shell->line); */
		/* printf("WC == [%d]\n", i);
		ft_putmtr(mtr); */
		//pwd();
		free_mtr(mtr);
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

