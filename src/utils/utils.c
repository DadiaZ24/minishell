#include "minishell.h"

void	ft_print_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		ft_printf("Info->[%s]\nType->[%d]", temp->info, temp->type);
		temp = temp->next;
	}
}
