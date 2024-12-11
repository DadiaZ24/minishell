#include "minishell.h"

int	check_is_dir(char *path)
{
	struct stat buffer;

	if (stat(path, &buffer) == -1)
		perror("stat");
	else if (S_ISDIR(buffer.st_mode))
		return (1);
	else if (S_ISREG(buffer.st_mode))
		return (2);
	return (0);
}

void	check_permission(t_executor *exec, char *path, int i)
{
	if (access(path, F_OK))
	{
		print_error(" Permission denied");
		free_process(exec);
		exit(1);
	}
	if (i == 1 && access(path, R_OK))
	{
		print_error(" Permission denied");
		free_process(exec);
		exit(1);
	}
	if (i == 2 && access(path, W_OK))
	{
		print_error(" Permission denied");
		free_process(exec);
		exit(1);
	}
	if (i == 3 && access(path, X_OK))
	{
		print_error(" Permission denied");
		free_process(exec);
		exit(1);
	}
}

void	handle_redirects(t_executor *exec, t_ast *ast)
{
	int	fd_in;
	int	fd_out;
	t_ast	*ast_temp;

	(void)exec;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	ast_temp = ast;
	
	while (ast_temp->parent && ast_temp->parent->type != PIPE)
	{
		ast_temp = ast_temp->parent;
		if (ast_temp->type == RED_OUT)
		{
			fd_out = open(ast_temp->red_target, O_CREAT | O_RDWR, 0777);
			check_permission(exec, ast_temp->red_target, 2);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (ast_temp->type == RED_IN)
		{
			fd_in = open(ast_temp->red_target, O_RDWR, 0777);
			check_permission(exec, ast_temp->red_target, 1);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else if (ast_temp->type == APPEND)
		{
			fd_out = open(ast_temp->red_target, O_APPEND | O_CREAT | O_RDWR, 0777);
			check_permission(exec, ast_temp->red_target, 2);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (check_is_dir(ast_temp->red_target) != 2)
		{
			print_error("Path is a directory");
			free_process(exec);
			exit(2);
		}
	}
}
