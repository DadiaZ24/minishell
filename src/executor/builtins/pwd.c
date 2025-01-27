#include "minishell.h"

int pwd(char **mtr, t_executor *exec)
{
	char cwd[MAX_PATH_LEN];

	(void)mtr;
	/* if (mtr[1] && mtr[1][0] != '-' && mtr[1][1])
	{
		if (exec->is_child)
		{
			printf("pwd: too many arguments");
			free_process(exec);
			exit(1);
		}
		else
			return (printf("pwd: too many arguments"), 0);
	} */
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		printf("ERROR READING PWD\n");
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	else
		return (set_exit_status(exec->shell, 0), 1);
	return (set_exit_status(exec->shell, 0), 1);
}
