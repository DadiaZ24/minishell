#include "minishell.h"

int	create_pid(t_executor *exec, t_ast **ast)
{
	int		i;
	t_ast	*temp_ast;

	i = 0;
	temp_ast = *ast;
	while (temp_ast)
	{
		if (temp_ast->type == PIPE)
			++i;
		temp_ast = temp_ast->parent;
	}
	exec->num_pipe = i + 1;
	exec->pid = (int *)malloc((i + 2) * sizeof(int));
	exec->pid[i + 1] = 0;
	return (i);
}

bool	handle_pipe(t_executor *exec, t_ast **ast)
{
	int	fd[2];
	int	i;
	t_ast *temp;

	i = 0;
	temp = *(exec->ast);
	while (temp)
	{
		if ((*ast)->type == ARG)
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
		}
		temp = temp->parent;
		*ast = temp->right;
	}
	dup2(exec->fd_out, STDOUT_FILENO);
	close(exec->fd_out);
	close(fd[0]);
	return (false);
}

bool	check_builtin(t_ast **ast)
{
	t_ast	*temp_ast;

	temp_ast = *(ast);
	if (!strncmp((temp_ast)->arg[0], "cd", ft_strlen((temp_ast)->arg[0])))
		return (true);
	else if (!strncmp((temp_ast)->arg[0], "pwd", ft_strlen((temp_ast)->arg[0])))
		return (true);
	else if (!strncmp((temp_ast)->arg[0], "echo", ft_strlen((temp_ast)->arg[0])))
		return (true);
	else if (!strncmp((temp_ast)->arg[0], "export", ft_strlen((temp_ast)->arg[0])))
		return (true);
	/*else if (!strncmp((*tokens)->info, "unset", ft_strlen((*tokens)->info)))
		//TODO
		(void);*/
	else if (!strncmp((temp_ast)->arg[0], "env", ft_strlen((temp_ast)->arg[0])))
		return (true);
	else if (!strncmp((temp_ast)->arg[0], "exit", ft_strlen((temp_ast)->arg[0])))
		return (true);
	return (false);
}

bool	builtin(t_executor *exec, t_ast **ast)
{
	t_ast	*temp_ast;

	temp_ast = *(ast);
	// handle_redirects(exec, temp_ast);
	if (!strncmp((temp_ast)->arg[0], "cd", ft_strlen((temp_ast)->arg[0])))
		cd(exec->shell, (temp_ast)->arg, exec);
	else if (!strncmp((temp_ast)->arg[0], "pwd", ft_strlen((temp_ast)->arg[0])))
		pwd((temp_ast)->arg, exec);
	else if (!strncmp((temp_ast)->arg[0], "echo", ft_strlen((temp_ast)->arg[0])))
		echo((temp_ast)->arg, exec);
	else if (!strncmp((temp_ast)->arg[0], "export", ft_strlen((temp_ast)->arg[0])))
		export(exec);
	/*else if (!strncmp((*tokens)->info, "unset", ft_strlen((*tokens)->info)))
		//TODO
		(void);*/
	else if (!strncmp((temp_ast)->arg[0], "env", ft_strlen((temp_ast)->arg[0])))
		env(exec->shell, (temp_ast)->arg, exec);
	else if (!strncmp((temp_ast)->arg[0], "exit", ft_strlen((temp_ast)->arg[0])))
		exit_builtin(exec->shell->status, exec);
	return (true);
}

int	executor(t_executor *exec)
{
	char	*str_path;
	t_ast	*temp_ast;
	int		r;

	r = 0;
	str_path = NULL;
	temp_ast = *(exec->ast);
	if (create_pid(exec, &temp_ast) == 0 && check_builtin(&temp_ast))
		return (free(exec->pid), exec->pid = NULL, builtin(exec, &temp_ast));
	if (handle_pipe(exec, &temp_ast))
		return (1);
	// handle_redirects(exec, temp_ast);
	if (check_builtin(&temp_ast))
		builtin(exec, &temp_ast);
	else
		exec_execve(&r, str_path, exec, temp_ast);
	return (1);
}

int exec_execve(int *r, char *str_path, t_executor *exec, t_ast *ast)
{
	t_ast	*temp_ast;

	temp_ast = ast;
	if (!ft_strncmp((temp_ast)->arg[0], "./", 2))
		str_path = ft_strdup((temp_ast)->arg[0]);
	else
		str_path = ft_strjoin("/usr/bin/", (temp_ast)->arg[0]);
	execve(str_path, (temp_ast)->arg, exec->shell->env);
	exit_exec(exec, temp_ast);
	*r = exec->shell->status;
	free(str_path);
	free_process(exec);
	exit(*r);
}
