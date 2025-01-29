#include "minishell.h"

int	check_quotes(t_token *token)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	while (token->info[++i])
	{
		if (quote == '\0')
		{
			if (token->info[i] == '\'' || token->info[i] == '\"')
				quote = token->info[i];
		}
		else if (quote == token->info[i])
			quote = '\0';
	}
	if (quote != '\0')
		return (printf("minishell: syntax error: unclosed quotes"
				"are not available due to subject rules\n"), 0);
	return (1);
}
