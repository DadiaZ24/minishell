#include "minishell.h"

bool env(t_shell *shell, char **mtr, t_executor *exec)
{
	int i;

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
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
	}
	if (exec->is_child)
	{
		free_process(exec);
		exit(1);
	}
	return (true);
}
