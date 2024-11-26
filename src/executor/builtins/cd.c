#include "minishell.h"

void cd(t_shell *shell, t_token **tokens)
{
	char current_path[MAX_PATH_LEN];
	char new_path[MAX_PATH_LEN];

	if(getcwd(current_path, sizeof(current_path)) == NULL)
	{
		printf("Error getting current path\n");
		return;
	}
	if(!(*tokens)->next || ((*tokens)->next->info && !ft_strcmp((*tokens)->next->info, "~")))
		chdir(getenvp(shell->export, "HOME"));
	else if ((*tokens)->next->next)
		printf("Too many arguments\n");
	else if ((*tokens)->next->info && !ft_strcmp((*tokens)->next->info, "-"))
		chdir(getenvp(shell->export, "OLDPWD"));
	else if ((*tokens)->next->info && !is_directory((*tokens)->next->info))
		printf("Not a directory\n");
	else if ((*tokens)->next->info && is_directory((*tokens)->next->info))
		chdir(ft_joinpath(current_path, (*tokens)->next->info));
	else
		printf("Invalid path\n");
	if(getcwd(new_path, sizeof(new_path)) == NULL)
		printf("Error getting new path\n");
	else
		update_pwd_env(shell->export, current_path, new_path);
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
			env[i] = oldpwd_line;
		if (!ft_strncmp(env[i], "PWD=", 4))
			env[i] = newpwd_line;
	}
}
