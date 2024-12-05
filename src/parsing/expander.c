#include "minishell.h"

void	free_exp_end(t_exp *exp)
{
	if (exp->joinstr[0] != '\0')
	{
		free(exp->joinstr);
		exp->joinstr = "\0";
	}
	free(exp->substr);
	exp->substr = NULL;
	free(exp->temp->info);
	exp->temp->info = NULL;
	exp->temp->info = ft_strdup(exp->str);
	free(exp->str);
	exp->str = NULL;
}

void	free_exp_str(t_exp *exp)
{
	free(exp->joinstr);
	exp->joinstr = NULL;
	free(exp->substr);
	exp->substr = NULL;
	exp->joinstr = ft_strdup(exp->str);
	free(exp->str);
	exp->str = NULL;
}

void	expander(t_token **token)
{
	t_exp	*exp;

	exp = NULL;
	exp = init_exp(exp, token);
	while (exp->temp)
	{
		if(exp->temp->type == ARG)
		{
			while (exp->temp->info[++exp->i])
			{
				if (ft_isquote(exp->temp->info[exp->i]) == 1)
				{
					while (ft_isquote(exp->temp->info[exp->i]) != 1)
						exp->i++;
					exp->start = exp->i + 1;
				}
				else if (ft_isquote(exp->temp->info[exp->i]) == 2)
				{
					exp->i++;
					while (ft_isquote(exp->temp->info[exp->i]) != 2)
					{
						if (exp->temp->info[exp->i] == '$' && exp->temp->info[exp->i - 1] != '\\')
						{
							exp->start = exp->i++;
							while (ft_isalnum(exp->temp->info[exp->i]))
								exp->i++;
						}
					}
				}
			}
			if (ft_isquote(exp->temp->info[exp->i] == 0))
			{
				exp->end = exp->i;
				exp->substr = ft_substr(exp->temp->info, exp->start, (exp->end - exp->start));
				exp->str = ft_strjoin(exp->joinstr, exp->substr);
				free_exp_end(exp);
			}
		}
		exp->temp = exp->temp->next;
	}
	free(exp);
}

