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
