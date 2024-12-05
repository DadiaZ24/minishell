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

void	expander(t_token **token, t_executor *exec)
{
	t_exp	*exp;

	exp = NULL;
	exp = init_exp(exp, token);
	while (exp->temp)
	{
		if(exp->temp->type == ARG)
		{
			while (exp->temp->info[++exp->str_i])
			{
				if (ft_isquote(exp->temp->info[exp->str_i]) == 1)
				{
					while (ft_isquote(exp->temp->info[exp->str_i]) != 1)
						exp->str_i++;
					exp->start = exp->str_i + 1;
				}
				else if (ft_isquote(exp->temp->info[exp->str_i]) == 2)
				{
					exp->str_i++;
					while (ft_isquote(exp->temp->info[exp->str_i]) != 2)
					{
						if (exp->temp->info[exp->str_i] == '$' && exp->temp->info[exp->str_i - 1] != '\\')
						{
							exp->start = ++exp->str_i;
							while (ft_isalnum(exp->temp->info[exp->str_i]))
								exp->str_i++;
							exp->end = exp->str_i;
							exp->substr = ft_substr(exp->temp->info, exp->start, (exp->end - exp->start));
							while (exec->shell->env[++exp->mtr_i])
							{
								if (ft_strncmp(exp->substr, exec->shell->env[exp->mtr_i], ft_strlen(exp->substr)) == 0)
								{
									if (exec->shell->env[exp->mtr_i][ft_strlen(exp->substr)] == '=')
									{
										exp->joinstr = ft_strjoin(exp->joinstr, exec->shell->env[exp->mtr_i] + ft_strlen(exp->substr) + 1);
										/* ERROR MUST DO */
										/* ERROR MUST DO */
										/* ERROR MUST DO */
										/* ERROR MUST DO */
										exp->build_sub = ft_substr(exp->temp->info, exp->start - 1, (exp->end - exp->start) + 1);
										exp->build = ft_strjoin(exp->build_sub, exp->joinstr);
										ft_printf("joinstr: %s\n", exp->joinstr);
										ft_printf("build_sub: %s\n", exp->build_sub);
										ft_printf("build: %s\n", exp->build);
									}
								}
							}
						}
						exp->str_i++;
					}
				}
			}
			if (ft_isquote(exp->temp->info[exp->str_i] == 0))
			{
				exp->end = exp->str_i;
				exp->substr = ft_substr(exp->temp->info, exp->start, (exp->end - exp->start));
				exp->str = ft_strjoin(exp->joinstr, exp->substr);
				free_exp_end(exp);
			}
		}
		exp->temp = exp->temp->next;
	}
	free(exp);
}

