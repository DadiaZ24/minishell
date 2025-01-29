#include "minishell.h"

char	**free_split(char **str, int j)
{
	while (j--)
		free(str[j]);
	free(str);
	return (NULL);
}

void	free_mtr(char **mtr)
{
	int	j;

	j = -1;
	if (!mtr)
		return ;
	while (mtr[++j])
		free(mtr[j]);
	free(mtr);
}

void	free_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		temp = token->next;
		free(token->info);
		free(token);
		token = temp;
	}
}

void	free_ast_utils(t_ast *ast)
{
	if (ast->left)
	{
		if (ast->left->arg)
			free_mtr(ast->left->arg);
		if (ast->left->red_target)
			free(ast->left->red_target);
		free(ast->left);
	}
	if (ast->right)
	{
		if (ast->right->arg)
			free_mtr(ast->right->arg);
		if (ast->right->red_target)
			free(ast->right->red_target);
		free(ast->right);
	}
}

/* void	free_ast(t_ast **ast)
{
	t_ast	*temp;

	temp = *ast;
	if (!temp)
		return ;
	if (temp->parent)
	{
		temp = temp->parent;
		while (temp->parent)
		{
			free_ast_utils(temp);
			temp = temp->parent;
		}
	}
	free_ast_utils(temp);
	if (temp->arg)
		free_mtr(temp->arg);
	if (temp->red_target)
		free(temp->red_target);
	free(temp);
} */

void	ft_free_cmds(t_cmds *cmds)
{
	t_cmds	*temp;

	while (cmds)
	{
		temp = cmds->next;
		if (cmds->cmd)
			free(cmds->cmd);
		if (cmds->args)
			free_mtr(cmds->args);
		if (cmds->redir)
			free_token(cmds->redir);
		free(cmds);
		cmds = temp;
	}
}
