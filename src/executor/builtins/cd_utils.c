#include "minishell.h"

void	cd_utils(t_shell *shell, char *new_path, char *current_path)
{
	char	*str;

	str = getcwd(new_path, sizeof(new_path));
	if (!new_path)
		printf("Error getting new path\n");
	else
		update_pwd_env(shell, current_path, str);
}

void	handle_child_process(t_executor *exec)
{
	free_process(exec);
	exec->shell->status = 0;
	exit(1);
}

int	cd_handles(t_shell *shell, char *new_path, char *current_path, char *handle_type)
{
	if (handle_type == "home_dir")
		return (chdir(getenvp(shell->env, "HOME")), 1);
	else if (handle_type == "many_args")
	{
		shell->status = 1;
		return (w_error(" too many arguments\n"), 1);
	}
	else if (handle_type == "oldpwd")
		return (chdir(getenvp(shell->env, "OLDPWD")), 1);
	else if (handle_type == "invalid_path")
	{
		shell->status = 1;
		return (printf("Invalid path\n"), 0);
	}
	else if (handle_type == "get_path_error")
	{
		shell->status = 1;
		if (exec->is_child)
		{
			free_process(exec);
			exit(1);
		}
		return (0);
	}
}

int handle_directory(t_shell *shell, bool is_directory, char **mtr, char *current_path)
{
	char *new_path;

	new_path = cd_utils(shell, mtr[1], current_path);
	if (is_directory)
	{
		chdir(new_path);
		free(new_path);
		shell->status = 0;
		return (1);
	}
	else
	{
		shell->status = 1;
		w_error(" No such file or directory\n");
		free(new_path);
		return (0);
	}
}
