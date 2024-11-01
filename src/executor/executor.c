#include "minishell.h"

char *get_cmd_path(char *cmd)
{
	
}


int	cmd_exec(t_cmd *cmd)
{
	pid_t pid = fork();

	if (pid = -1)
		return (perror("failed to get pid"), -1);
	else if (pid == 0)

}