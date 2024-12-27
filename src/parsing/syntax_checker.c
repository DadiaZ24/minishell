#include "minishell.h"

int syntax_checker(t_token **tokens)
{
	t_token *token;

	token = *tokens;
	if (!token || token->info[0] == '\0')
		return (printf("\n"), 0);
	/*if (!check_quotes(tokens))
		return (0);*/
	while (token)
	{
		if (!syntax_pipe(token) || !syntax_red_out_in(token) || !syntax_append_heredoc(token))
			return (0);
		token = token->next;
	}
	return (1);
}

int syntax_pipe(t_token *token)
{
	if (token->type == PIPE && !token->next)
		return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
	if (token->type == PIPE && !token->prev)
		return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
	if (token->type == PIPE && token->next->type == PIPE)
		return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
	return (1);
}

int syntax_red_out_in(t_token *token)
{
	if (token->type == RED_OUT && !token->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == RED_OUT && !token->prev)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == RED_OUT && (token->next->type == RED_OUT || token->next->type == APPEND || token->next->type == HERE_DOC || token->next->type == PIPE || token->next->type == RED_IN))
		return (printf("minishell: syntax error near unexpected token `>'\n"), 0);
	if (token->type == RED_IN && !token->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == RED_IN && !token->prev)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == RED_IN && (token->next->type == RED_IN || token->next->type == APPEND || token->next->type == HERE_DOC || token->next->type == PIPE || token->next->type == RED_OUT))
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	return (1);
}

int syntax_append_heredoc(t_token *token)
{
	if (token->type == APPEND && !token->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == APPEND && !token->prev)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == APPEND && (token->next->type == APPEND || token->next->type == RED_OUT || token->next->type == HERE_DOC || token->next->type == PIPE || token->next->type == RED_IN))
		return (printf("minishell: syntax error near unexpected token `>>'\n"), 0);
	if (token->type == HERE_DOC && !token->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == HERE_DOC && !token->prev)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
	if (token->type == HERE_DOC && (token->next->type == HERE_DOC || token->next->type == RED_OUT || token->next->type == APPEND || token->next->type == PIPE || token->next->type == RED_IN))
		return (printf("minishell: syntax error near unexpected token `<<'\n"), 0);
	return (1);
}
