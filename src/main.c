#include "minishell.h"

int	minishell(t_shell *shell, t_token **tokens, char **envp)
{
	(void)envp;
	t_ast	**ast;
	char	**mtr;

	mtr = NULL;
	ast = (t_ast **)malloc(sizeof(t_ast));
	if (!ast)
		return (0);
	while (1)
	{
		shell->line = readline("minishell$ ");
		if (!shell->line)
			return (free(tokens), free(ast), printf("exit\n"), 0);
		if (shell->line)
			add_history(shell->line);
		mtr = mini_split(shell->line);
		create_token(mtr, tokens);
		lexer(tokens);
		create_ast(tokens, ast);
		ft_print_ast(*ast);
		free_mtr(mtr);
		free(shell->line);
		free_token(tokens);
	}
}

void	create_tokens(t_token **tokens, char **mtr)
{
	t_token	*temp;
	char	**temp_str;

	temp = *tokens;
	temp_str = mtr;
	while (*temp_str)
	{
		ft_add_token(tokens, ft_newtoken(1, *temp_str));
		temp = temp->next;
		temp_str++;
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
	return (0);
}

