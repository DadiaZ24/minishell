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
	exec->num_pipe = i;
	if (i == 0)
		return (i);
	exec->pid = (int *)malloc((i + 1) * sizeof(int));
	exec->pid[i] = 0;
	return (i);
}

bool	handle_pipe(t_executor *exec)
{
	int	fd[2];
	int	i;
	t_cmds *temp;

	i = 0;
	temp = *(exec->cmds);
	while (temp)
	{
		pipe(fd);
		if ((exec->pid[i++] = fork()))
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (i == exec->num_pipe)
				return (dup2(exec->fd_in, STDIN_FILENO), true);
		}
		else
		{
			exec->is_child = true;
			if (i == exec->num_pipe)
				break;
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
			return (false);
		}
		temp = temp->next;
	}
	dup2(exec->fd_out, STDOUT_FILENO);
	close(exec->fd_out);
	close(fd[0]);
	return (false);
}

bool	check_builtin(t_cmds **cmds)
{
	t_cmds	*temp_cmds;

	temp_cmds = *(cmds);
	if (!strncmp((temp_cmds)->cmd, "cd", ft_strlen((temp_cmds)->cmd)))
		return (true);
	else if (!strncmp((temp_cmds)->cmd, "pwd", ft_strlen((temp_cmds)->cmd)))
		return (true);
	else if (!strncmp((temp_cmds)->cmd, "echo", ft_strlen((temp_cmds)->cmd)))
		return (true);
	else if (!strncmp((temp_cmds)->cmd, "export", ft_strlen((temp_cmds)->cmd)))
		return (true);
	/*else if (!strncmp((*tokens)->info, "unset", ft_strlen((*tokens)->info)))
		//TODO
		(void);*/
	else if (!strncmp((temp_cmds)->cmd, "env", ft_strlen((temp_cmds)->cmd)))
		return (true);
	else if (!strncmp((temp_cmds)->cmd, "exit", ft_strlen((temp_cmds)->cmd)))
		return (true);
	return (false);
}

bool	builtin(t_executor *exec, t_cmds **cmds)
{
	t_cmds	*temp_cmds;

	temp_cmds = *(cmds);
	//handle_redirects(exec, temp_cmds);
	if (!strncmp((temp_cmds)->cmd, "cd", ft_strlen((temp_cmds)->cmd)))
		cd(exec->shell, (temp_cmds)->args, exec);
	else if (!strncmp((temp_cmds)->cmd, "pwd", ft_strlen((temp_cmds)->cmd)))
		pwd((temp_cmds)->args, exec);
	else if (!strncmp((temp_cmds)->cmd, "echo", ft_strlen((temp_cmds)->cmd)))
		echo((temp_cmds)->args, exec);
	else if (!strncmp((temp_cmds)->cmd, "export", ft_strlen((temp_cmds)->cmd)))
		export(exec);
	/*else if (!strncmp((*tokens)->info, "unset", ft_strlen((*tokens)->info)))
		//TODO
		(void);*/
	else if (!strncmp((temp_cmds)->cmd, "env", ft_strlen((temp_cmds)->cmd)))
		env(exec->shell, (temp_cmds)->args, exec);
	else if (!strncmp((temp_cmds)->cmd, "exit", ft_strlen((temp_cmds)->cmd)))
		exit_builtin(exec->shell->status, exec);
	return (true);
}

int	executor(t_executor *exec)
{
	char	*str_path;
	t_cmds	*temp_cmds;
	int		r;

	r = 0;
	str_path = NULL;
	temp_cmds = *(exec->cmds);
	if (create_pid(exec, &temp_cmds) == 0 && check_builtin(&temp_cmds))
		return (free(exec->pid), exec->pid = NULL, builtin(exec, &temp_cmds));
	if (handle_pipe(exec))
		return (1);
	//handle_redirects(exec, temp_cmds);
	if (check_builtin(&temp_cmds))
		builtin(exec, &temp_cmds);
	else
		exec_execve(&r, str_path, exec, temp_cmds);
	return (1);
}

int exec_execve(int *r, char *str_path, t_executor *exec, t_cmds *cmds)
{
	t_cmds	*temp_cmds;

	temp_cmds = cmds;
	if (!ft_strncmp((temp_cmds)->cmd, "./", 2))
		str_path = ft_strdup((temp_cmds)->cmd);
	else
		str_path = ft_strjoin("/usr/bin/", (temp_cmds)->cmd);
	execve(str_path, (temp_cmds)->args, exec->shell->env);
	exit_exec(exec, temp_cmds);
	*r = exec->shell->status;
	free(str_path);
	free_process(exec);
	exit(*r);
}
