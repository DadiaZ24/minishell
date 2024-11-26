#include "minishell.h"

bool	echo(t_shell *shell, t_token **tokens)
{
	int i;

	i = 0;
	(void)shell;
	if (!(*tokens)->next)
		return (printf("\n"), false);
	if ((*tokens)->next && (*tokens)->next->info[0] == '-')
	{
		while ((*tokens)->next->info[i] == 'n')
			i++;
		if ((*tokens)->next->info[i] != 'n')
			return (write(1, "\0", 1), true);
		else
			return (write(1, "\n", 1), true);
	
	}
	return (true);
}
