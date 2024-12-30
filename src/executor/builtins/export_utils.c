#include "minishell.h"

bool bubblesort(t_executor *exec)
{
	int i;
	int j;
	char *temp;

	i = 0;
	while (exec->shell->env[i])
	{
		j = i + 1;
		while (exec->shell->env[j])
		{
			if (ft_strncmp(exec->shell->env[i], exec->shell->env[j], ft_strlen(exec->shell->env[i]) + 1) > 0)
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
