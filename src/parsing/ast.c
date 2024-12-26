#include "minishell.h"

t_ast_utils	*init_au(t_token **token, t_ast **ast)
{
	t_ast_utils	*au;

	au = malloc((1) * sizeof(t_ast_utils));
	if (!au)
	{
		// Need to check error code
		ft_printf("%s\n", "Error");
		exit(1);
	}
	au->i = 0;
	au->branch = *token;
	au->temp = *token;
	au->ast_temp = *ast;
	return (au);
}

t_ast	*ast_node(t_token *start, t_token *end, t_ast *ast)
{
	t_token	*temp;
	int	i;
	int	j;

	temp = start;
	i = 1;
	j = -1;
	while (start != end)
	{
		start = start->next;
		++i;
	}
	ast->arg = malloc(sizeof(char *) * (i + 1));
	while (++j < i)
	{
		ast->arg[j] = ft_strdup(temp->info);
		temp = temp->next;
	}
	ast->arg[j] = NULL;
	ast->type = ARG;
	return (ast);
}

void	create_ast(t_token **token, t_ast **ast)
{
	t_ast_utils	*au;

	au = init_au(token, ast);
	while (au->branch)
	{
		if (ft_pipe_or_redirect(au->branch->info) > 0 && au->i++ == 0)
			ast_utils_red(au, ast);
		else if (ft_pipe_or_redirect(au->branch->info) > 0)
		{
			au->i = 1;
			if (check_redirect_or_pipe(au->branch->info) == PIPE)
				ast_utils_pipe(au, ast);
			else
				ast_utils_other_than_pipe(au, ast);
		}
		else
			ast_utils_else(au, ast);
		au->temp = au->branch;
	}
	free(au);
}
