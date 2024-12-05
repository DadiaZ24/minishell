#include "minishell.h"

t_exp	*init_exp(t_exp	*exp, t_token **token)
{
	exp = (t_exp *)malloc(sizeof(t_exp));
	exp->str_i = -1;
	exp->mtr_i = -1;
	exp->start = 0;
	exp->end = 0;
	exp->str = NULL;
	exp->joinstr = "\0";
	exp->build = NULL;
	exp->build_sub = NULL;
	exp->substr = NULL;
	exp->temp = *token;
	return (exp);
}
