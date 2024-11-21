#include "minishell.h"

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

t_ast	**create_ast(t_token **token, t_ast **ast)
{
	int		i;
	t_token	*temp;
	t_token	*branch;
	t_ast	*ast_temp;

	i = 0;
	branch = *token;
	temp = branch;
	ast_temp = *ast;
	while (temp)
	{
		if (ft_pipe_or_redirect(branch->info) && i++ == 0)
		{
			*ast = init_ast(*ast);
			if (!(*ast))
				return (NULL);
			(*ast)->type = branch->type;
			(*ast)->red_target = ft_strdup(branch->next->info);
			branch = branch->next;
			if (branch->next)
			{
				branch = branch->next;
				temp = branch;
				while (branch->next && ft_pipe_or_redirect(branch->info) == 0)
					branch = branch->next;
				(*ast)->left = init_ast((*ast)->left);
				if (!branch->next)
					(*ast)->left = ast_node(temp, branch, (*ast)->left);
				else
					(*ast)->left = ast_node(temp, branch->prev, (*ast)->left);
				(*ast)->left->parent = *ast;
				ast_temp = *ast;
				(*ast) = (*ast)->left;
			}
		}
		else if (ft_pipe_or_redirect(branch->info))
		{
			if (check_redirect_or_pipe(branch->info) == PIPE)
			{
				ast_temp->type = branch->type;
				branch = branch->next;
				temp = branch;
				while (branch->next && ft_pipe_or_redirect(branch->info) == 0)
					branch = branch->next;
				ast_temp->right = init_ast(*ast);
				if (!branch->next)
					ast_temp->right = ast_node(temp, branch, ast_temp->right);
				else
					ast_temp->right = ast_node(temp, branch->prev, ast_temp->right);
				ast_temp->right->parent = ast_temp;
				ast_temp->parent = NULL;
				if (branch->next)
					ast_temp->parent = init_ast(ast_temp->parent);
				ast_temp = ast_temp->parent;
			}
		}
		else
		{
			while (branch->next && ft_pipe_or_redirect(branch->info) == 0)
				branch = branch->next;
			*ast = init_ast(*ast);
			if (!branch->next)
				*ast = ast_node(temp, branch, *ast);
			else
				*ast = ast_node(temp, branch->prev, *ast);
			if (branch->next)
			{
				(*ast)->parent = init_ast(ast_temp->parent);
				ast_temp = (*ast)->parent;
				ast_temp->left = *ast;
			}
			else
				(*ast)->parent = NULL;
		}
		temp = branch->next;
	}
	return (ast);
}
