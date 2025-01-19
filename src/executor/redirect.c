#include "minishell.h"

int	check_is_dir(char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) == -1)
		perror("stat");
	else if (S_ISDIR(buffer.st_mode))
		return (1);
	else if (S_ISREG(buffer.st_mode))
		return (2);
	return (0);
}

static bool	handle_permission_error(t_executor *exec)
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

static bool	check_specific_permission(t_executor *exec, char *path, int i)
{
	if (access(path, i))
		return (handle_permission_error(exec));
	return (true);
}

bool	check_permission(t_executor *exec, char *path, int i)
{
	if (!check_specific_permission(exec, path, i))
		return (false);
	if (i == 1 && !check_specific_permission(exec, path, R_OK))
		return (false);
	if (i == 2 && !check_specific_permission(exec, path, W_OK))
		return (false);
	if (i == 3 && !check_specific_permission(exec, path, X_OK))
		return (false);
	return (true);
}

bool	handle_redirects(t_executor *exec, t_cmds *cmds)
{
	int	fd_in;
	int	fd_out;
	t_token	*temp;

	(void)exec;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	temp = cmds->redir;
	
	while (temp)
	{
		if (temp->type == RED_OUT)
		{
			fd_out = open(temp->info, O_CREAT | O_RDWR, 0777);
			if  (!check_permission(exec, temp->info, 2))
				return (false);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (temp->type == RED_IN)
		{
			fd_in = open(temp->info, O_RDWR, 0777);
			if  (!check_permission(exec, temp->info, 1))
				return (false);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else if (temp->type == APPEND)
		{
			fd_out = open(temp->info, O_APPEND | O_CREAT | O_RDWR, 0777);
			if  (!check_permission(exec, temp->info, 2))
				return (false);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (temp->type == HERE_DOC)
		{
			fd_in = open(temp->info, O_RDONLY, 0777);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			return (true);
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
