#include "minishell.h"

bool env(t_shell *shell, char **mtr, t_executor *exec)
{
	int i;

	update_env(shell);
	i = -1;
	if (mtr[1])
	{
		printf("env: can not receive arguments or options (imposed by subject)\n");
		if (exec->is_child)
		{
			free_process(exec);
			exit(1);
		}
		return (1);
	}
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	if (exec->is_child)
	{
		free_process(exec);
		exit(1);
	}
	return (true);
}

void update_env(t_shell *shell)
{
	int i;
	int j;

	i = -1;
	while (shell->env[++i])
	{
		j = -1;
		while(shell->export[++j])
		{
			if (ft_strncmp(shell->env[i], shell->export[j], ft_strclen(shell->export[j], '=') + 1) == 0)
			{
				free(shell->env[i]);
				shell->env[i] = ft_strdup(shell->export[j]);
				break;
			}
		}
	}
}
