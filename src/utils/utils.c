#include "minishell.h"

void	ft_print_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		ft_printf("Info->[%s]\nType->[%d]\n", temp->info, temp->type);
		temp = temp->next;
	}
}

char	*mini_fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

void	ft_print_ast(t_ast *ast)
{
	ft_printf("=======================================\n");
	ft_printf("Type->[%d]\n", ast->type);
	ft_putmtr(ast->arg);
	ft_printf("Red->[%s]\n", ast->red_target);
	ft_printf("=======================================\n");
	if (ast->parent)
	{
		ast = ast->parent;
		while (ast)
		{
			if (ast->right)
			{
				ft_printf("=======================================\n");
				ft_printf("Type->[%d]\n", ast->right->type);
				ft_putmtr(ast->right->arg);
				ft_printf("Red->[%s]\n", ast->right->red_target);
				ft_printf("=======================================\n");
			}
			ft_printf("=======================================\n");
			ft_printf("Type->[%d]\n", ast->type);
			ft_putmtr(ast->arg);
			ft_printf("Red->[%s]\n", ast->red_target);
			ft_printf("=======================================\n");
			ast = ast->parent;
		}
	}
}
