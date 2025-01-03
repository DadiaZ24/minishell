#include "minishell.h"

int create_pid(t_executor *exec, t_cmds **cmds)
{
	int i;
	t_cmds *temp_cmds;

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

bool handle_pipe(t_executor *exec, t_cmds **temp)
{
	int fd[2];
	int i;

	i = 0;
	while (*temp)
	{
		pipe(fd);
		if ((exec->pid[i++] = fork()))
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (!(*temp)->next)
				return (dup2(exec->fd_in, STDIN_FILENO), true);
			*temp = (*temp)->next;
		}
		else
		{
			exec->is_child = true;
			if (!(*temp)->next)
				break;
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			return (false);
		}
	}
	dup2(exec->fd_out, STDOUT_FILENO);
	close(exec->fd_out);
	close(fd[0]);
	return (false);
}

bool check_builtin(t_cmds **cmds)
{
	t_cmds *temp_cmds;

	temp_cmds = *(cmds);
	if (!strcmp((temp_cmds)->cmd, "cd"))
		return (true);
	else if (!strcmp((temp_cmds)->cmd, "pwd"))
		return (true);
	else if (!strcmp((temp_cmds)->cmd, "echo"))
		return (true);
	else if (!strcmp((temp_cmds)->cmd, "export"))
		return (true);
	else if (!strcmp((temp_cmds)->cmd, "unset"))
		return (true);
	else if (!strcmp((temp_cmds)->cmd, "env"))
		return (true);
	else if (!strcmp((temp_cmds)->cmd, "exit"))
		return (true);
	return (false);
}

bool builtin(t_executor *exec, t_cmds **cmds)
{
	t_cmds *temp_cmds;

	temp_cmds = *(cmds);
	if (!handle_redirects(exec, temp_cmds))
		return (false);
	if (!strcmp((temp_cmds)->cmd, "cd"))
		cd(exec->shell, (temp_cmds)->args, exec);
	else if (!strcmp((temp_cmds)->cmd, "pwd"))
		pwd((temp_cmds)->args, exec);
	else if (!strcmp((temp_cmds)->cmd, "echo"))
		echo((temp_cmds)->args, exec);
	else if (!strcmp((temp_cmds)->cmd, "export"))
		export(exec);
	else if (!strcmp((temp_cmds)->cmd, "unset"))
		unset((temp_cmds)->args, exec);
	else if (!strcmp((temp_cmds)->cmd, "env"))
		env(exec->shell, (temp_cmds)->args, exec);
	else if (!strcmp((temp_cmds)->cmd, "exit"))
		exit_builtin(exec->shell->status, exec, (temp_cmds)->args);
	return (true);
}

int executor(t_executor *exec)
{
	char *str_path;
	t_cmds *temp_cmds;
	int r;

	r = 0;
	str_path = NULL;
	temp_cmds = *(exec->cmds);
	if (ft_strlen(temp_cmds->cmd) == 0 && !temp_cmds->d_quotes)
		return (1);
	if (create_pid(exec, &temp_cmds) == 1 && check_builtin(&temp_cmds))
		return (free(exec->pid), exec->pid = NULL, builtin(exec, &temp_cmds));
	if (handle_pipe(exec, &temp_cmds))
		return (1);
	if (!handle_redirects(exec, temp_cmds))
		return (1);
	if (check_builtin(&temp_cmds))
		builtin(exec, &temp_cmds);
	else
		exec_execve(&r, str_path, exec, temp_cmds);
	return (1);
}

int exec_execve(int *r, char *str_path, t_executor *exec, t_cmds *cmds)
{
	t_cmds *temp_cmds;

	temp_cmds = cmds;
	if (!ft_strncmp((temp_cmds)->cmd, "./", 2))
		str_path = ft_strdup((temp_cmds)->cmd);
	else
		str_path = ft_strjoin("/usr/bin/", (temp_cmds)->cmd);
	if (execve(str_path, (temp_cmds)->args, exec->shell->env) == -1)
	{
		if (exec->is_child)
			exit(127);
		printf("minishell: %s: command not found\n", (temp_cmds)->cmd);
		set_exit_status(exec->shell, 127);
	}
	exit_exec(exec, temp_cmds);
	*r = exec->shell->status;
	free(str_path);
	free_process(exec);
	exit(*r);
}
