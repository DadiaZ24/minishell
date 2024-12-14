#include "minishell.h"

char **new_entry(char **env, char *entry, int i)
{
	while (env[i])
		i++;
	env = realloc_env(env, i);
	env[i] = ft_strdup_quotes(entry);
	env[i + 1] = NULL;
	return (env);
}

bool update_entry(char **env_entry, char *entry, bool is_new, int size)
{
	(void)is_new;
	if (ft_strchr(entry, '+'))
	{
		if (ft_strncmp(*env_entry, entry, size - 3) == 0)
		{
			is_new = false;
			*env_entry = ft_strjoin(*env_entry, entry + size + 1);
		}
		else
		{
			is_new = true;
			return (false);
		}

	}
	else
	{
		if (ft_strncmp(*env_entry, entry, size == 0))
		{
			is_new = false;
			free(*env_entry);
			*env_entry = ft_strdup(entry);
		}
		else
		{
			is_new = true;
			return (false);
		}
	}
	return (true);
}

int	print_export(t_executor *exec, char **env)
{
	int i;

	bubblesort(exec);
	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
	return (1);
}

int	export(t_executor *exec)
{
	t_cmds	*temp_ast;
	int		i;
	bool	is_new;

	temp_ast = *(exec->cmds);
	i = -1;
	is_new = true;
	if (temp_ast->args[0] && !temp_ast->args[1])
	{
		print_export(exec, exec->shell->env);
		return (1);
	}
	else if (temp_ast->args[1])
	{
		i = 0;
		while (temp_ast->args[++i])
			exec->shell->env = export_body_update(temp_ast->args[i], exec->shell->env, is_new);
	}
	return (1);
}

char	**export_put_values(char **env, char *arg, int i)
{
	char	*temp;
	int		j;

	j = -1;
	while (env[++j])
	{
		if (ft_strncmp(env[j], arg, i) == 0)
		{
			temp = ft_strdup(env[j]);
			free(env[j]);
			env[j] = ft_strdup(arg);
			free(temp);
			break;
		}
	}
	return (env);
}

char	**handle_entry(char *arg, char **env, bool is_new, char delimiter)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (delimiter == '+')
		{
			if (update_entry(&env[i], arg, is_new, ft_strclen(arg, delimiter) + 2))
			{
				is_new = false;
				break;
			}
		}
		else
		{
			if (update_entry(&env[i], arg, is_new, ft_strclen(arg, delimiter) + 1))
			{
				is_new = false;
				break;
			}
		}
	}
	if (is_new)
		env = new_entry(env, arg, i);
	return (env);
}

bool	has_append_operator(char *arg)
{
	if (!arg)
		return (false);
	while (*arg)
	{
		if (*arg == '+' && *(arg + 1) == '=')
			return (true);
		arg++;
	}
	return (false);
}

char	**export_body_update(char *arg, char **env, bool is_new)
{
	if (has_append_operator(arg))
		return (handle_entry(arg, env, is_new, '+'));
	else if (ft_strchr(arg, '=') && !has_append_operator(arg))
		return (handle_entry(arg, env, is_new, '='));
	return (handle_entry(arg, env, is_new, '='));
}



char **realloc_env (char **env, int i)
{
	char **new_env;
	int j;

	j = -1;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (0);
	while (env[++j])
	{
		new_env[j] = ft_strdup(env[j]);
		free(env[j]);
	}
	new_env[j] = NULL;
	free(env[j]);
	free(env);
	return (new_env);
}
