#include "minishell.h"

int	main(void)
{
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token));
	if (!tokens)
		return (0);
	minishell(tokens);
	free_tokens(tokens);
	return (1);
}
