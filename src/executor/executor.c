#include "minishell.h"

int	create_pid(t_executor *exec, t_cmds **cmds)
{
	int		i;
	t_cmds	*temp_cmds;

	i = 0;
	temp_cmds = *cmds;
	while (temp_cmds)
	{
		++i;
		temp_cmds = temp_cmds->next;
	}
	exec->n_process = i;
	if (i == 0)
		return (i);
	exec->pid = (int *)malloc((i + 1) * sizeof(int));
	exec->pid[i] = 0;
	return (i);
}

static bool	handle_parent_process(t_executor *exec, t_cmds **temp, int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (!(*temp)->next)
		return (dup2(exec->fd_in, STDIN_FILENO), true);
	*temp = (*temp)->next;
	return (false);
}

static bool	handle_child_process(t_executor *exec, t_cmds *temp, int fd[2])
{
	exec->is_child = true;
	if (!temp->next)
		return (true);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (false);
}

bool	handle_pipe(t_executor *exec, t_cmds **temp)
{
	int	fd[2];
	int	i;

	i = 0;
	while (*temp)
	{
		pipe(fd);
		exec->pid[i] = fork();
		if (exec->pid[i++] != 0)
		{
			if (handle_parent_process(exec, temp, fd))
				return (true);
		}
		else
		{
			if (handle_child_process(exec, *temp, fd))
				break ;
			return (false);
		}
	}
	dup2(exec->fd_out, STDOUT_FILENO);
	close(exec->fd_out);
	close(fd[0]);
	return (false);
}
