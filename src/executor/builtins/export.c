/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:25:25 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/06 14:25:25 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_child(t_executor *exec, int exit_code)
{
	free_process(exec);
	exit(exit_code);
}

static int	export_with_args(t_export *export, t_cmds *cmd, t_executor *exec)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (parse_export(cmd->args[i], export))
		{
			if (!execute_export(export, exec))
			{
				if (exec->is_child)
					exit_child(exec, 1);
				return (set_exit_status(exec->shell, 1),
					free_export(export), 1);
			}
			else
			{
				if (exec->is_child)
					exit_child(exec, 0);
				free_export_args(export);
			}
		}
		else
			return (set_exit_status(exec->shell, 1), free_export(export), 1);
	}
	return (free_export(export), 0);
}

int	export(t_executor *exec)
{
	t_cmds		*cmd;
	t_export	*export;

	cmd = *(exec->cmds);
	export = malloc(sizeof(t_export));
	if (!export)
		return (0);
	export = init_export(export, exec);
	if (cmd->args[0] && !cmd->args[1])
	{
		print_export(export);
		if (exec->is_child)
			exit_child(exec, 0);
		return (set_exit_status(exec->shell, 0), free_export(export), 1);
	}
	else if (cmd->args[1])
		return (export_with_args(export, cmd, exec));
	return (set_exit_status(exec->shell, 0), 1);
}

void	print_export(t_export *export)
{
	int	i;

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

char	**realloc_env(char **env)
{
	char	**new_env;
	int		j;
	int		len;

	j = -1;
	len = env_len(env);
	new_env = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (0);
	while (env[++j])
		new_env[j] = ft_strdup(env[j]);
	new_env[j] = NULL;
	new_env[j + 1] = NULL;
	free_mtr(env);
	return (new_env);
}
