#include "minishell.h"

int export(t_executor *exec)
{
	t_cmds *cmd;
	t_export *export;
	int i;

	cmd = *(exec->cmds);
	i = -1;
	export = malloc(sizeof(t_export));
	if (!export)
		return (0);
	export = init_export(export, exec);
	if (cmd->args[0] && !cmd->args[1])
	{
		print_export(export);
		if (exec->is_child)
		{
			free_process(exec);
			exit(0);
		}
		return (set_exit_status(exec->shell, 0), free_export(export), 1);
	}
	else if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (parse_export(cmd->args[i], export))
			{
				if (!execute_export(export, exec))
				{
					if (exec->is_child)
					{
						free_process(exec);
						exit(1);
					}
					return (set_exit_status(exec->shell, 1), free_export(export), 1);
				}
			}
			else
				return (set_exit_status(exec->shell, 1), free_export(export), 1);
		}
		return (free_export(export), 1);
	}
	return (set_exit_status(exec->shell, 0), free_export(export), 1);
}

void	execute_append(t_export *export, t_executor *exec)
{
	int i;

	i = -1;
	if (!export->new_entry)
	{
		while(exec->shell->env[++i])
		{
			if (ft_strncmp(export->arg_left, exec->shell->env[i], ft_strlen(export->arg_left) - 1) == 0)
			{
				if (exec->shell->env[i][ft_strlen(export->arg_left) - 1] == '=')
				{
					exec->shell->env[i] = ft_strjoin(exec->shell->env[i], export->arg_right);
					break;
				}
			}
		}
	}
	else
		make_new_entry(export, exec);

}

bool make_new_entry(t_export *export, t_executor *exec)
{
	exec->shell->env = realloc_env(exec->shell->env);
	if (!exec->shell->env)
		return (false);
	exec->shell->env[env_len(exec->shell->env)] = ft_strjoin(ft_strjoin(export->arg_left, "="), export->arg_right);
	return (true);
}

bool replace_entry(t_export *export, t_executor *exec)
{
	int i;

	i = -1;
	while(exec->shell->env[++i])
	{
		if (ft_strncmp(export->arg_left, exec->shell->env[i], ft_strlen(export->arg_left)) == 0)
		{
				free(exec->shell->env[i]);
				exec->shell->env[i] = ft_strjoin(ft_strjoin(export->arg_left, "="), export->arg_right);
				break;
		}
	}
	return (true);
}

bool	execute_export(t_export *export, t_executor *exec)
{
	if (export->do_nothing)
		return (false);
	if (export->arg_equals)
	{
		if (export->append)
			return (execute_append(export, exec), true);
		else
		{
			if (export->new_entry)
				return (make_new_entry(export, exec), true);
			else
				return (replace_entry(export, exec), true);
		}
	}
	return (true);
}

void print_export(t_export *export)
{
	int i;

	bubblesort(export);
	i = -1;
	while (export->key_left[++i])
	{
		printf("declare -x %s", export->key_left[i]);
		if (export->key_right[i])
			printf("=\"%s\"\n", export->key_right[i]);
		else
			printf("\n");
	}
}

bool parse_export_equal(char *arg, t_export *export)
{
	size_t i;

	i = -1;
	export->arg_right = ft_strdup(ft_strchr(arg, '=') + 1);
	export->arg_equals = true;
	export->do_nothing = false;
	if (export->arg_left[ft_strlen(export->arg_left) - 1] == '+')
		export->append = true;
	while (export->arg_left[++i])
	{
		if (export->append && i == ft_strlen(export->arg_left) - 1 && export->arg_left[i] == '+')
			break;
		if ((!ft_isalpha(export->arg_left[i]) && export->arg_left[i] != '_')  || ft_strlen(export->arg_left) == 0)
			return (printf("minishell: export: `%s': not a valid identifier\n", arg), false);
	}
	i = -1;
	return (true);
}

bool parse_export_no_equal(t_export *export)
{
	size_t i;

	i = -1;
	export->arg_right = NULL;
	export->arg_equals = false;
	while (export->arg_left[++i])
	{
		if ((!ft_isalpha(export->arg_left[i]) && export->arg_left[i] != '_')  || ft_strlen(export->arg_left) == 0)
			return (printf("minishell: export: `%s': not a valid identifier\n", export->arg_left), false);
	}
	if (!export->new_entry)
		export->do_nothing = true;
	else
		export->do_nothing = false;
	return (true);
}

bool parse_export(char *arg, t_export *export)
{
	int i;

	i = -1;
	if (arg[0] == '=' || arg[0] == '+')
		return (printf("minishell: export: `%s': not a valid identifier\n", arg), false);
	if (arg[0] == '-')
		return (printf("minishell: export: options are not suposed\n"), false);
	export->arg_left = ft_strndup(arg, ft_strclen(arg, '='));
	export->new_entry = true;
	while (export->key_left[++i])
	{
		if (ft_strcmp(export->key_left[i], export->arg_left) == 0 && !ft_strchr(export->arg_left, '+'))
		{
			export->new_entry = false;
			break;
		}
		else if (ft_strncmp(export->key_left[i], export->arg_left, ft_strlen(export->arg_left) - 1) == 0 && ft_strchr(export->arg_left, '+'))
		{
			export->new_entry = false;
			export->append = true;
			break;
		}
	}
	i = -1;
	if (ft_strchr(arg, '='))
		return (parse_export_equal(arg, export));
	else
		return (parse_export_no_equal(export));
	return (true);
}

char **realloc_env(char **env)
{
	char **new_env;
	int j;

	j = -1;
	new_env = (char **)malloc(sizeof(char *) * (env_len(env) + 2));
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
