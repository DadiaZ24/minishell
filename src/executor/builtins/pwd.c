#include "minishell.h"

int	pwd(char **mtr, t_executor *exec)
{
	char	cwd[MAX_PATH_LEN];

	if (mtr[1] && mtr[1][0] != '-' && mtr[1][1])
	{
		if (exec->is_child)
		{
			printf("pwd: too many arguments");
			free_process(exec);
			exit(1);
		}
		else
			return (printf("pwd: too many arguments"), 0);
	}
	if (getcwd(cwd, sizeof(cwd)))
			printf("%s\n", cwd);
	else
		printf("ERROR READING PWD\n");
	if (exec->is_child)
	{
		free_process(exec);
		exit(1);
	}
	else
		return (1);
	return (1);
}
