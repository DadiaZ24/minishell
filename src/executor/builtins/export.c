#include "minishell.h"

int export(t_executor *exec)
{
	t_cmds *temp_ast;
	int i;
	bool is_new;

	temp_ast = *(exec->cmds);
	i = -1;
	is_new = true;
	if (temp_ast->args[0] && !temp_ast->args[1])
	{
		print_export(exec, exec->shell->env);
		if (exec->is_child)
		{
			free_process(exec);
			exit(0);
		}
		return (set_exit_status(exec->shell, 0), 1);
	}
	else if (temp_ast->args[1])
	{
		i = 0;
		while (temp_ast->args[++i])
			exec->shell->env = export_body_update(temp_ast->args[i], exec->shell->env, is_new, exec);
		if (exec->is_child)
		{
			free_process(exec);
			exit(0);
		}
		return (1);
	}
	return (set_exit_status(exec->shell, 0), 1);
}

int print_export(t_executor *exec, char **env)
{
	int i;
	char **key;

	key = malloc(sizeof(char *) * 2);
	if (!key)
		return (0);
	bubblesort(exec);
	i = -1;
	while (env[++i])
	{
		key[0] = ft_strndup(env[i], ft_strclen(env[i], '='));
		if (ft_strchr(env[i], '='))
			key[1] = ft_strchr(env[i], '=') + 1;
		printf("declare -x %s", key[0]);
		if (key[1])
			printf("=\"%s\"\n", key[1]);
		else
			printf("\n");
		free(key[0]);
		key[1] = NULL;
	}
	free(key);
	return (1);
}

char **export_body_update(char *arg, char **env, bool is_new, t_executor *exec)
{
	if (has_append_operator(arg))
		return (handle_entry(arg, env, is_new, '+'));
	else if (arg[0] && arg[0] == '+')
		return (set_exit_status(exec->shell, 1), w_error("minishell: not a valid identifier\n"), env);
	else if (has_operator_before_equal(arg) || (arg[0] && arg[0] == '='))
	{
		exec->shell->status = 1;
		return (set_exit_status(exec->shell, 1), w_error("minishell: not a valid identifier\n"), env);
	}
	else if (ft_strchr(arg, '-') && !ft_strchr(arg, '='))
	{
		exec->shell->status = 1;
		return (env);
	}
	else if (ft_strchr(arg, '=') && ft_strlen(arg) == 1)
	{
		exec->shell->status = 1;
		return (env);
	}
	else if (ft_isdigit(arg[0]))
		return (set_exit_status(exec->shell, 1), w_error("minishell: not a valid identifier\n"), env);
	else if (ft_strchr(arg, '=') && !has_append_operator(arg))
		return (handle_entry(arg, env, is_new, '='));
	return (handle_entry(arg, env, is_new, '='));
}

char **handle_entry(char *arg, char **env, bool is_new, char delimiter)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (delimiter == '+')
		{
			if (update_entry(&env[i], arg, ft_strclen(arg, delimiter)))
			{
				is_new = false;
				break;
			}
		}
		else
		{
			if (update_entry(&env[i], arg, ft_strclen(arg, delimiter) + 1))
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

bool update_entry(char **env_entry, char *entry, int size)
{
	if (ft_strchr(entry, '+'))
	{
		if (ft_strncmp(*env_entry, entry, size) == 0)
			if (!ft_strchr(*env_entry, '='))
				*env_entry = join_entry(*env_entry, entry, size + 1);
			else
				*env_entry = join_entry(*env_entry, entry, size + 2);
		else
			return (false);
	}
	else
	{
		if (!ft_strncmp(*env_entry, entry, size) == 0)
		{
			free(*env_entry);
			*env_entry = ft_strdup(entry);
		}
		else
		{
			*env_entry = join_entry(*env_entry, entry, size - 1);
			return (false);
		}
	}
	return (true);
}

char **new_entry(char **env, char *entry, int i)
{
	int		j;
	bool	check;

	j = -1;
	check = false;
	if (check_if_exists(entry, env))
		return (env);
	while (env[i])
		i++;
	while (entry[++j])
	{
		if ((entry[j] == '+' && (entry[j + 1] && entry[j + 1] == '=') && !check_if_exists(entry, env)))
		{
			check = true;
			break ;
		}
	}
	env = realloc_env(env, i);
	if (check)
		env[i] = swap_export(entry, j);
	else
		env[i] = ft_strdup(entry);
	env[i + 1] = NULL;
	return (env);
}

char	*swap_export(char *entry, int j)
{
	char	*temp;
	char	*temp_join;

	temp_join = NULL;
	temp = NULL;
	temp = ft_substr(entry, 0, j);
	temp_join = ft_substr(entry, j + 1, ft_strlen(entry));
	entry = ft_strjoin(temp, temp_join);
	free(temp);
	free(temp_join);
	return (entry);
}

char **export_put_values(char **env, char *arg, int i)
{
	char *temp;
	int j;

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

bool has_append_operator(char *arg)
{
	if (!arg)
		return (false);
	if (arg[0] && arg[0] == '+')
		return (false);
	while (*arg)
	{
		if (*arg == '+' && *(arg + 1) == '=')
			return (true);
		if (*arg == '+' && *(arg + 1) == '+')
			return (false);
		arg++;
	}
	return (false);
}

bool has_operator_before_equal(char *arg)
{
	if (!arg)
		return (false);
	if (ft_strchr(arg, '='))
	{
		while (*arg)
		{
			if (*(arg + 1) == '=' && ft_isalnum(*arg))
				break;
			if ((!ft_isalnum(*arg) && *arg != '_') && *arg != '=')
				return (true);
			if (*arg == '=' && !(*(arg + 1)))
				return (true);
			arg++;
		}
	}
	else
	{
		while (*arg)
		{
			if ((!ft_isalnum(*arg) && *arg != '_'))
				return (true);
			arg++;
		}
	}
	return (false);
}

char **realloc_env(char **env, int i)
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

bool	check_if_exists(char *arg, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(arg, env[i], ft_strclen(env[i], '=')))
			return (true);
	}
	i = -1;
	/* while (arg[++i])
	{
		if (arg[i] == '+' && (arg[i + 1] && arg[i + 1] == '=') && (arg[i - 1] && arg[i - 1] != '='))
			return (true);
	} */
	return (false);
}

char	*join_entry(char *env_entry, char *entry, int size)
{
	void	*new_entry;

	new_entry = ft_strjoin(env_entry, entry + size);
	free(env_entry);
	return (new_entry);
}
