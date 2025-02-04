#include "minishell.h"

int export(t_executor *exec)
{
	t_cmds *cmd;
	t_export *export;
	int i;
	bool is_new;

	cmd = *(exec->cmds);
	i = -1;
	export = init_export(export, exec);
	if (cmd->args[0] && !cmd->args[1])
	{
		print_export(exec, exec->shell->env);
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
				// EXECUTE EXPORT
			}
		}
		return (1);
	}
	return (set_exit_status(exec->shell, 0), 1);
}

int print_export(t_export *export)
{
	int i;

	bubblesort(exec);
	i = -1;
	while (export->key_left[++i])
	{
		printf("declare -x %s", export->key_left[i]);
		if (export->key_right[i])
			printf("=\"%s\"\n", export->key_right[i]);
		else
			printf("\n");
	}
	return (1);
}

bool parse_export_equal(char *arg, t_export *export)
{
	int i;

	i = -1;
	export->arg_right = ft_strdup(ft_strchr(arg, '=') + 1);
	if (export->arg_left[ft_strlen(export->arg_left)] == '+')
		export->append = true;
	while (export->arg_left[++i])
	{
		if (export->append && i == ft_strlen(export->arg_left) - 1)
			break;
		if ((!ft_isalpha(export->arg_left[i]) && export->arg_left[i] != '_')  || ft_strlen(export->arg_left) == 0)
			return (false);
	}
	i = -1;
	if (export->arg_right)
	{
		while (export->arg_right[++i])
		{
			if ((!ft_isalnum(export->arg_right[i]) && export->arg_right[i] != '_'))
				return (false);
		}
	}
}

bool parse_export_no_equal(char *arg, t_export *export)
{
	export->arg_right = NULL;
	while (export->arg_left[++i])
	{
		if ((!ft_isalpha(export->arg_left[i]) && export->arg_left[i] != '_')  || ft_strlen(export->arg_left) == 0)
			return (false);
	}
}

bool parse_export(char *arg, t_export *export)
{
	int i;

	i = -1;
	if (arg[0] == '=' || arg[0] == '+')
		return (false);
	export->arg_left = ft_strndup(arg, ft_strclen(arg, '='));
	if (ft_strchr(arg, '='))
		return (parse_export_equal(arg, export));
	else
		return (parse_export_no_equal(arg, export));
	return (true);
}

char **export_body_update(char *arg, t_export *export)
{
	export->arg_left = ft_strndup(arg, ft_strclen(arg, '='));
	if (ft_strchr(arg, '=') && ft_isdigit(arg[0]))
	{
		export->arg_right = ft_strdup(ft_strchr(arg, '=') + 1);
		if (check_append(arg))
		{
			
		}
	}
}
