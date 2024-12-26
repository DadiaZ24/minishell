#include "minishell.h"

void cd_utils(t_shell *shell, char *new_path, char *current_path)
{
	char *str;

	str = getcwd(new_path, sizeof(new_path));
	if (!new_path)
		printf("Error getting new path\n");
	else
		update_pwd_env(shell, current_path, str);
}

int cd(t_shell *shell, char **mtr, t_executor *exec)
{
	char current_path[MAX_PATH_LEN];
	char new_path[MAX_PATH_LEN];
	char *str;

	str = NULL;
	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		printf("Error getting current path\n");
		exec->shell->status = 1;
		if (exec->is_child)
		{
			free_process(exec);
			exit(1);
		}

		return (1);
	}
	if (!mtr[1] || (mtr[1] && !ft_strcmp(mtr[1], "~")))
		chdir(getenvp(shell->env, "HOME"));
	else if (mtr[2])
	{
		exec->shell->status = 1;
		w_error(" too many arguments\n");
	}
	else if (mtr[1] && !ft_strcmp(mtr[1], "-"))
		chdir(getenvp(shell->env, "OLDPWD"));
	else if (mtr[1] && !is_directory(mtr[1]))
	{
		exec->shell->status = 1;
		w_error(" No such file or directory\n");
	}
	else if (mtr[1] && is_directory(mtr[1]))
	{
		str = ft_joinpath(current_path, mtr[1]);
		chdir(str);
		free(str);
		cd_utils(shell, new_path, current_path);
	}
	else
	{
		printf("Invalid path\n");
		exec->shell->status = 1;
	}
	if (exec->is_child)
	{
		free_process(exec);
		exec->shell->status = 0;
		exit(1);
	}
	exec->shell->status = 0;
	return (1);
}

void update_pwd_env(t_shell *shell, char *oldpwd, char *newpwd)
{
	char *oldpwd_line;
	char *newpwd_line;
	int i;

	i = -1;
	oldpwd_line = ft_strjoin("OLDPWD=", oldpwd);
	newpwd_line = ft_strjoin("PWD=", newpwd);
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], "OLDPWD=", 7))
		{
			free(shell->env[i]);
			shell->env[i] = oldpwd_line;
		}
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
		{
			free(shell->env[i]);
			shell->env[i] = newpwd_line;
		}
	}
}
