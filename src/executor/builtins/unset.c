#include <minishell.h>

int	unset(t_executor *exec)
{
	t_ast	*temp_ast;
	int		i;
	int		j;

	temp_ast = *(exec->ast);
	i = -1;
	while(temp_ast->arg[++i])
	{
		j = -1;
		while (exec->shell->env[++j])
		{
			if (ft_strncmp(exec->shell->env[j], temp_ast->arg[i], ft_strlen(temp_ast->arg[i])) == 0)
			{
				free(exec->shell->env[j]);
				exec->shell->env[j] = NULL;
				if (!realloc_unset(exec))
					return (0);
				break;
			}
		}
	}
	return (1);
}

int	realloc_unset(t_executor *exec)
{
	int		i;
	int		j;
	char	**new_env;

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
