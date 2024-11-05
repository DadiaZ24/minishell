#include "minishell.h"

void	ft_print_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		ft_printf("Info->[%s]\nType->[%d]", temp->info, temp->type);
		temp = temp->next;
	}
}
void	ft_add_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lsttoken(*lst);
	temp->next = new;
	temp->next->prev = temp;
}

t_token	*ft_lsttoken(t_token *token)
{
	t_token *lst;

	lst = token;
	if (!lst)
		return (0);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_token	*ft_newtoken(int type, char *info)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->info = info;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}