#include "minishell.h"

t_exp	*init_exp(t_exp	*exp, t_token **token)
{
	exp = (t_exp *)malloc(sizeof(t_exp));
	exp->bin = false;
	exp->start = 0;
	exp->str_i = -1;
	exp->mtr_i = -1;
	exp->env_i = -1;
	exp->temp = NULL;
	exp->swap = NULL;
	exp->token = *token;
	return (exp);
}

void	create_token_loop(char **mtr, t_token *temp, int i)
{
	temp->next = (t_token *)malloc(sizeof(t_token));
	if (!(temp->next))
		return ;
	temp->next->prev = temp;
	temp = temp->next;
	temp->info = ft_strdup(mtr[i]);
	temp->type = false;
	temp->type = -1;
	temp->d_quotes = false;
	temp->next = NULL;
}
