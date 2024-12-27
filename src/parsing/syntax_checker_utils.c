#include "minishell.h"

int check_quotes(t_token **tokens, char quote)
{
	int i;
	bool has_open_quote;
	t_token *token;

	i = -1;
	has_open_quote = false;
	token = (*tokens)->next;
	while (token)
	{
		while (token->info[++i])
		{
			if (token->info[i] == quote)
				has_open_quote = !has_open_quote;
		}
		token = token->next;
	}
	if (has_open_quote)
		return (printf("minishell: syntax error: unclosed quotes are not available due to subject rules\n"), 0);
	return (1);
}