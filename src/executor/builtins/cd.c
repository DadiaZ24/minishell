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

int cd(t_shell *shell, char **mtr, t_executor *exec)
{
	char current_path[MAX_PATH_LEN];
	char new_path[MAX_PATH_LEN];
	char *str;

	str = NULL;
	if(getcwd(current_path, sizeof(current_path)) == NULL)
	{
		printf("Error getting current path\n");
		if (exec->is_child)
		{
			free_process(exec);
			exit(1);
		}
		return (1);
	}
	if(!mtr[1] || (mtr[1] && !ft_strcmp(mtr[1], "~")))
		chdir(getenvp(shell->export, "HOME"));
	else if (mtr[2])
		printf("Too many arguments\n");
	else if (mtr[1] && !ft_strcmp(mtr[1], "-"))
		chdir(getenvp(shell->export, "OLDPWD"));
	else if (mtr[1] && !is_directory(mtr[1]))
		printf("Not a directory\n");
	else if (mtr[1] && is_directory(mtr[1]))
	{
		str = ft_joinpath(current_path, mtr[1]);
		chdir(str);
		free(str);
		cd_utils(shell, new_path, current_path);
	}
	else
		printf("Invalid path\n");
	if (exec->is_child)
	{
		free_process(exec);
		exit(1);
	}
	return (1);
}

void	update_pwd_env(t_shell *shell, char *oldpwd, char *newpwd)
{
	char *oldpwd_line;
	char *newpwd_line;
	int i;

	i = -1;
	oldpwd_line = ft_strjoin("OLDPWD=", oldpwd);
	newpwd_line = ft_strjoin("PWD=", newpwd);
	while (shell->export[++i])
	{
		if (!ft_strncmp(shell->export[i], "OLDPWD=", 7))
		{
			free(shell->export[i]);
			shell->export[i] = oldpwd_line;
		}
		if (!ft_strncmp(shell->export[i], "PWD=", 4))
		{
			free(shell->export[i]);
			shell->export[i] = newpwd_line;
		}
	}
}
