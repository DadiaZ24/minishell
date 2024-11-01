#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*temp;
	
	temp = *tokens;
	while (temp)
	{
		temp = (*tokens)->next;
		temp->prev = NULL;
		free(*tokens);
		*tokens = temp;
	}
	free(tokens);
	exit(1);
}

void	ft_free_mtr(char **str)
{
	int	j;

	j = -1;
	while (str[++j])
		free(str[j]);
	free(str);
}
