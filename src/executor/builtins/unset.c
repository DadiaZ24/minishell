#include <minishell.h>

int realloc_unset(t_executor *exec)
{
	int i;
	int j;
	char **new_env;

	i = -1;
	j = 0;
	while (exec->shell->env[++i])
	{
		if (exec->shell->env[i])
			j++;
	}
	new_env = malloc(sizeof(char *) * (j + 1));
	if (!new_env)
		return (0);
	i = -1;
	j = -1;
	while (exec->shell->env[++i])
	{
		if (exec->shell->env[i])
			new_env[++j] = ft_strdup(exec->shell->env[i]);
	}
	new_env[j] = NULL;
	free(exec->shell->env);
	exec->shell->env = new_env;
	return (1);
}

int unset(char **mtr, t_executor *exec)
{
	int i;
	int j;

	i = -1;
	while (mtr[++i])
	{
		j = -1;
		while (exec->shell->env[++j])
		{
			if (ft_strncmp(exec->shell->env[j], mtr[i], ft_strlen(mtr[i])) == 0)
			{
				free(exec->shell->env[j]);
				exec->shell->env[j] = NULL;
				if (!realloc_unset(exec))
					return (set_exit_status(exec->shell, 1), 0);
				break;
			}
		}
	}
	return (set_exit_status(exec->shell, 0), 1);
}
