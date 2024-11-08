#include "minishell.h"

char	**free_split(char **str, int j)
{
	while (j--)
		free(str[j]);
	free(str);
	return (NULL);
}

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
