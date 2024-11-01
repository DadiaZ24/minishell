#include "minishell.h"

void	pwd(void)
{
	char cwd[MAX_PATH_LEN];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		printf("ERROR READING PWD\n");
}
