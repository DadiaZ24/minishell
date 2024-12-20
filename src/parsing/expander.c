#include "minishell.h"

int	get_env_var(t_exp *exp, t_executor *exec)
{
	int	i;

	i = -1;
	while (exec->shell->env[++exp->mtr_i])
	{
		if (ft_strncmp(exp->token->info + exp->start, exec->shell->env[exp->mtr_i], exp->str_i - exp->start) == 0 
			&& exec->shell->env[exp->mtr_i][exp->str_i - exp->start] == '=')
			i = exp->mtr_i;
	}
	exp->mtr_i = -1;
	return (i);
}

void	swap_exp(t_exp *exp)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr(exp->token->info, exp->start, exp->str_i - exp->start);
	exp->swap = ft_strjoin(exp->temp, temp);
	free(temp);
	if (exp->temp)
	{
		free(exp->temp);
		exp->temp = NULL;
	}
	exp->temp = ft_strdup(exp->swap);
	free(exp->swap);
	exp->swap = NULL;
}

void	swap_exp_dollar(t_exp *exp)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr(exp->token->info, exp->start, (exp->str_i + 1) - exp->start);
	exp->swap = ft_strjoin(exp->temp, temp);
	free(temp);
	if (exp->temp)
	{
		free(exp->temp);
		exp->temp = NULL;
	}
	exp->temp = ft_strdup(exp->swap);
	free(exp->swap);
	exp->swap = NULL;
}

void	check_exp_temp_dollar(t_exp *exp)
{
	if (exp->temp)
		swap_exp_dollar(exp);
	else
		exp->temp = ft_substr(exp->token->info, exp->start, (exp->str_i - exp->start));
	exp->start++;
}

void	swap_exp_code(t_exp *exp, t_executor *exec)
{
	char	*temp;

	temp = NULL;
	temp = ft_itoa(exec->shell->status);
	exp->swap = ft_strjoin(exp->temp, temp);
	free(temp);
	if (exp->temp)
	{
		free(exp->temp);
		exp->temp = NULL;
	}
	exp->temp = ft_strdup(exp->swap);
	free(exp->swap);
	exp->swap = NULL;
}

void	check_exp_temp_code(t_exp *exp, t_executor *exec)
{
	if (exp->temp)
		swap_exp_code(exp, exec);
	else
		exp->temp = ft_itoa(exec->shell->status);
	exp->str_i = exp->str_i + 1;
	exp->start = exp->str_i + 1;
}

void	check_exp_temp(t_exp *exp)
{
	if (exp->temp)
		swap_exp(exp);
	else
		exp->temp = ft_substr(exp->token->info, exp->start, (exp->str_i - exp->start));
}

void	expand(t_exp *exp, t_executor *exec)
{
	if (exp->env_i != -1)
	{
		exp->swap = ft_strjoin(exp->temp, exec->shell->env[exp->env_i] + (exp->str_i - exp->start) + 1);
		free(exp->temp);
		exp->temp = NULL;
		exp->temp = ft_strdup(exp->swap);
		free(exp->swap);
		exp->swap = NULL;
	}
	exp->start = exp->str_i--;
}

void	expander(t_token **token, t_executor *exec)
{
	t_exp	*exp;

	exp = NULL;
	exp = init_exp(exp, token);
	while (exp->token)
	{
		if(exp->token->type == ARG)
		{
			while (exp->token->info[++exp->str_i])
			{
				if (ft_isquote(exp->token->info[exp->str_i]) == 1 && !exp->bin)
				{
					check_exp_temp(exp);
					exp->start = ++exp->str_i;
					while (ft_isquote(exp->token->info[exp->str_i]) != 1)
							exp->str_i++;
					if (exp->start != exp->str_i)
						check_exp_temp(exp);
					exp->start = exp->str_i + 1;
				}
				else
				{
					if (exp->token->info[exp->str_i] == 92)
					{
						check_exp_temp(exp);
						if (exp->token->info[exp->str_i + 1])
							exp->start = ++exp->str_i;
						else
							exp->start = exp->str_i + 1;
					}
					else if (ft_isquote(exp->token->info[exp->str_i]) == 2 && !exp->bin)
					{
						check_exp_temp(exp);
						exp->start = exp->str_i + 1;
						exp->bin = true;
					}
					else if (ft_isquote(exp->token->info[exp->str_i]) == 2 && exp->bin)
					{
						check_exp_temp(exp);
						exp->start = exp->str_i + 1;
						exp->bin = false;
					}
					else if (exp->token->info[exp->str_i] == '$' && ft_iswhitespc(exp->token->info[exp->str_i + 1]) > 0)
					{
						check_exp_temp(exp);
						exp->start = exp->str_i;
					}
					else if (exp->token->info[exp->str_i] == '$')
					{
						check_exp_temp(exp);
						exp->start = exp->str_i;
						if (exp->token->info[exp->str_i + 1] == '?')
							check_exp_temp_code(exp, exec);
						else if ((exp->token->info[exp->str_i + 1] == '"' && !exp->bin) || (exp->token->info[exp->str_i + 1] == '\'' && !exp->bin))
							exp->start = exp->str_i + 1;
						else if ((exp->token->info[exp->str_i + 1] == '"' && exp->bin) || !exp->token->info[exp->str_i + 1])
							check_exp_temp_dollar(exp);
						else
						{
							exp->start = ++exp->str_i;
							while (ft_isalnum(exp->token->info[exp->str_i]) || exp->token->info[exp->str_i] == '_')
								++exp->str_i;
							exp->env_i = get_env_var(exp, exec);
							expand(exp, exec);
						}
					}
				}
			}
			if (exp->start != exp->str_i)
				check_exp_temp(exp);
		}
		if (exp->token->type == ARG)
		{
			free(exp->token->info);
			exp->token->info = ft_strdup(exp->temp);
			free(exp->temp);
			exp->temp = NULL;
			if (exp->swap)
			{
				free(exp->swap);
				exp->swap = NULL;
			}
			exp->env_i = -1;
			exp->str_i = -1;
			exp->start = 0;
			exp->token = exp->token->next;
		}
		else
			exp->token = exp->token->next;
	}
	free(exp);
}
