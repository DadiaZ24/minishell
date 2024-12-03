#include "minishell.h"

int	pwd(char **mtr)
{
	char	cwd[MAX_PATH_LEN];

	if (mtr[1] && mtr[1][0] != '-' && mtr[1][1])
		return (printf("pwd: too many arguments"), 0);
	if (getcwd(cwd, sizeof(cwd)))
			printf("%s\n", cwd);
	else
		printf("ERROR READING PWD\n");
	return (1);
}
