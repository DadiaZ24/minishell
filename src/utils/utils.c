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
	ft_printf("======\n");
	ft_printf("Type->[%d]\nArg->[", ast->type);
	ft_putmtr(ast->arg);
	ft_printf("]\nRed->[%s]\n======\n", ast->red_target);
	if (ast->parent)
	{
		ast = ast->parent;
		while (ast)
		{
			if (ast->right)
			{
				ft_printf("======\n");
				ft_printf("Type->[%d]\nArg->[", ast->right->type);
				ft_putmtr(ast->right->arg);
				ft_printf("]\nRed->[%s]\n======\n", ast->right->red_target);
			}
			ft_printf("======\n");
			ft_printf("Type->[%d]\nArg->[", ast->type);
			ft_putmtr(ast->arg);
			ft_printf("]\nRed->[%s]\n======\n", ast->red_target);
			ast = ast->parent;
		}
	}
}

void	print_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
}
