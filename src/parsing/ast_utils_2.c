#include "minishell.h"

void	ast_utils_else(t_ast_utils *au, t_ast **ast)
{
	au->i = 1;
	while (au->branch->next && ft_pipe_or_redirect(au->branch->info) == 0)
		au->branch = au->branch->next;
	*ast = init_ast(*ast);
	if (!au->branch->next)
		*ast = ast_node(au->temp, au->branch, *ast);
	else
		*ast = ast_node(au->temp, au->branch->prev, *ast);
	if (au->branch->next)
	{
		(*ast)->parent = init_ast((*ast)->parent);
		au->ast_temp = (*ast)->parent;
		au->ast_temp->left = *ast;
	}
	else
	{
		(*ast)->parent = NULL;
		au->branch = au->branch->next;
	}
}
