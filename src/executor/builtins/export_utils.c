#include "minishell.h"

bool bubblesort(t_executor *exec)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (exec->shell->env[i])
	{
		j = i + 1;
		while (exec->shell->env[j])
		{
			if (exec->shell->env[i][0] > exec->shell->env[j][0])
			{
				temp = exec->shell->env[i];
				exec->shell->env[i] = exec->shell->env[j];
				exec->shell->env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (1);
}
