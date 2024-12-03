#include "minishell.h"

int cd(t_shell *shell, char **mtr)
{
	char current_path[MAX_PATH_LEN];
	char new_path[MAX_PATH_LEN];
	char *str;

	str = NULL;
	if(getcwd(current_path, sizeof(current_path)) == NULL)
		return (printf("Error getting current path\n"), 0);
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
	}
	else
		printf("Invalid path\n");
	if(getcwd(new_path, sizeof(new_path)) == NULL)
		printf("Error getting new path\n");
	else
		update_pwd_env(shell->export, current_path, new_path);
	return (1);
}

void update_pwd_env(char **env, char *oldpwd, char *newpwd)
{
	char *oldpwd_line;
	char *newpwd_line;
	int i;

	i = -1;
	oldpwd_line = ft_strjoin("OLDPWD=", oldpwd);
	newpwd_line = ft_strjoin("PWD=", newpwd);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			free(env[i]);
			env[i] = oldpwd_line;
		}
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			free(env[i]);
			env[i] = newpwd_line;
		}
	}
}
