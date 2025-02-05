#include "minishell.h"

int	check_is_dir(char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) == -1)
		return (0);
	else if (S_ISDIR(buffer.st_mode))
		return (1);
	else if (S_ISREG(buffer.st_mode))
		return (2);
	return (0);
}

bool	check_permission(t_executor *exec, char *path, int i)
{
	if (access(path, F_OK))
	{
		print_error(" No such file or directory");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	if (i == 1 && access(path, R_OK))
	{
		print_error(" Permission denied");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	if (i == 2 && access(path, W_OK))
	{
		print_error(" Permission denied");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	if (i == 3 && access(path, X_OK))
	{
		print_error(" Permission denied");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	return (true);
}

bool	handle_redirects(t_executor *exec, t_cmds *cmds)
{
	int		fd_in;
	int		fd_out;
	t_token	*temp;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	temp = cmds->redir;
	while (temp)
	{
		if (temp->type == RED_OUT)
		{
			fd_out = open(temp->info, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (!check_permission(exec, temp->info, 2))
				return (false);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (temp->type == RED_IN)
		{
			fd_in = open(temp->info, O_RDWR, 0777);
			if (!check_permission(exec, temp->info, 1))
				return (false);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else if (temp->type == APPEND)
		{
			fd_out = open(temp->info, O_APPEND | O_CREAT | O_RDWR, 0777);
			if (!check_permission(exec, temp->info, 2))
				return (false);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (temp->type == HERE_DOC)
		{
			fd_in = open(temp->info, O_RDONLY, 0777);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (check_is_dir(temp->info) != 2)
		{
			print_error("Path is a directory");
			if (!exec->is_child)
			{
				exec->shell->status = 1;
				return (false);
			}
			free_process(exec);
			exit(2);
		}
		temp = temp->next;
	}
	return (true);
}
