#include "minishell.h"

int	pwd(t_token **tokens)
{
	char	cwd[MAX_PATH_LEN];

	while ((*tokens)->next)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		if ((*tokens)->info[0] == '-')
			return (printf("Invalid option\n"), 0);
	}
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		printf("ERROR READING PWD\n");
	return (1);
}
