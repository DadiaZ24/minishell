#include "minishell.h"

void	create_token(char **mtr, t_token **token)
{
	int		i;
	t_token	*temp;

	i = 0;
	*token = (t_token *)malloc(sizeof(t_token));
	if (!(*token))
		return ;
	(*token)->info = ft_strdup(mtr[i]);
	(*token)->type = -1;
	(*token)->prev = NULL;
	temp = *token;
	while (mtr[++i])
	{
		temp->next = (t_token *)malloc(sizeof(t_token));
		if (!(temp->next))
			return ;
		temp->next->prev = temp;
		temp = temp->next;
		temp->info = ft_strdup(mtr[i]);
		temp->type = -1;
		temp->next = NULL;
	}
}
