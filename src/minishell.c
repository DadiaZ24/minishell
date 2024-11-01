#include "minishell.h"

void	minishell(t_token **tokens)
{
	char	*str;
	
	while(true)
	{
		str = readline("Minishell: ");
		mini_split(str);
	}
}
