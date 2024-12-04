#include "minishell.h"

int is_directory(char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (1);
	}
	return (0);
}

char	*getenvp(char **envp, char *var)
{
	int i;
	int j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == var[j] && envp[i][j] != '=')
			j++;
		if (envp[i][j] == '=')
			return (envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

void	wait_pid(t_executor *exec)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!exec->pid)
		return ;
	while(exec->pid[i] != 0)
	{
		// printf("wait pid -----> [%d]\n", menu->pid_arr[i]);
		waitpid(exec->pid[i++], &j, 0);
		exec->shell->status = WEXITSTATUS(j);
	}
	free(exec->pid);
	exec->pid = NULL;
}