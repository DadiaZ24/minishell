#include "minishell.h"

void	ast_utils_red_utils(t_ast_utils *au, t_ast **ast)
{
	au->branch = au->branch->next;
	au->temp = au->branch;
	while (au->branch->next && ft_pipe_or_redirect(au->branch->info) == 0)
		au->branch = au->branch->next;
	ft_printf("TEST: %s\n", au->branch->info);
	(*ast)->left = init_ast((*ast)->left);
	if (!au->branch->next)
		(*ast)->left = ast_node(au->temp, au->branch, (*ast)->left);
	else
	{
		(*ast)->left = ast_node(au->temp, au->branch->prev, (*ast)->left);
		(*ast)->parent = init_ast((*ast)->parent);
		au->ast_temp = (*ast)->parent;
	}
	(*ast)->left->parent = *ast;
	(*ast) = (*ast)->left;
}

void	ast_utils_red(t_ast_utils *au, t_ast **ast)
{
	*ast = init_ast(*ast);
	if (!(*ast))
		return ;
	(*ast)->type = au->branch->type;
	(*ast)->red_target = ft_strdup(au->branch->next->info);
	au->branch = au->branch->next;
	if (au->branch->next)
		ast_utils_red_utils(au, ast);
	if (!au->branch->next)
		au->branch = au->branch->next;
}

void	ast_utils_pipe(t_ast_utils *au, t_ast **ast)
{
	au->ast_temp->type = au->branch->type;
	au->branch = au->branch->next;
	au->temp = au->branch;
	if (ft_pipe_or_redirect(au->branch->info) == 0)
	{
		while (au->branch->next && ft_pipe_or_redirect(au->branch->info) == 0)
			au->branch = au->branch->next;
		au->ast_temp->right = init_ast(*ast);
		if (!au->branch->next)
			au->ast_temp->right = ast_node(au->temp, au->branch, au->ast_temp->right);
		else
			au->ast_temp->right = ast_node(au->temp, au->branch->prev, au->ast_temp->right);
		au->ast_temp->right->parent = au->ast_temp;
		au->ast_temp->parent = NULL;
	}
	if (au->branch->next)
	{
		au->ast_temp->parent = init_ast(au->ast_temp->parent);
		au->ast_temp->parent->left = au->ast_temp;
	}
	au->ast_temp = au->ast_temp->parent;
	if (!au->branch->next)
		au->branch = au->branch->next;
}

void	ast_utils_other_than_pipe_utils(t_ast_utils *au, t_ast **ast)
{
	au->ast_temp->right = init_ast(*ast);
	if (!au->branch->next)
		au->ast_temp->right = ast_node(au->temp, au->branch, au->ast_temp->right);
	else
		au->ast_temp->right = ast_node(au->temp, au->branch->prev, au->ast_temp->right);
	au->ast_temp->right->parent = au->ast_temp;
	au->ast_temp->parent = NULL;
}

void	ast_utils_other_than_pipe(t_ast_utils *au, t_ast **ast)
{
	au->ast_temp->type = au->branch->type;
	au->ast_temp->red_target = ft_strdup(au->branch->next->info);
	au->branch = au->branch->next->next;
	au->temp = au->branch;
	if (!au->branch)
		return ;
	while (au->branch && au->branch->next && ft_pipe_or_redirect(au->branch->info) == 0)
		au->branch = au->branch->next;
	if (ft_strcmp(au->branch->info, au->ast_temp->red_target) != 0)
		ast_utils_other_than_pipe_utils(au, ast);
	if (au->branch->next)
	{
		au->ast_temp->parent = init_ast(au->ast_temp->parent);
		au->ast_temp->parent->left = au->ast_temp;
	}
	au->ast_temp = au->ast_temp->parent;
	if (!au->branch->next)
		au->branch = au->branch->next;
}
