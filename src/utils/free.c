#include "minishell.h"

void	free_mtr(char **mtr)
{
	int	j;

	j = -1;
	while (mtr[++j])
		free(mtr[j]);
	free(mtr);
}

void	free_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		temp = (*token)->next;
		free(*token);
		*token = temp;
		(*token)->prev = NULL;
	}
	free(token);
}

