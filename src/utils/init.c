#include "minishell.h"

void	create_token(char **mtr, t_token **token)
{
	int		i;
	t_token	*temp;

	i = 0;
	if (!mtr[i])
		return ;
	*token = (t_token *)malloc(sizeof(t_token));
	if (!(*token))
		return ;
	(*token)->info = ft_strdup(mtr[i]);
	(*token)->type = -1;
	(*token)->prev = NULL;
	temp = *token;
	while (mtr[++i])
	{
		temp->next = (t_token *)malloc(sizeof(t_token));
		if (!(temp->next))
			return ;
		temp->next->prev = temp;
		temp = temp->next;
		temp->info = ft_strdup(mtr[i]);
		temp->type = -1;
		temp->next = NULL;
	}
}

t_split	*init_split_var(void)
{
	t_split	*split;

	split = malloc((1) * sizeof(t_split));
	if (!split)
	{
		// Need to check error code
		ft_printf("%s\n", "Error");
		exit(1);
	}
	split->i = -1;
	split->j = 0;
	split->s_word = -1;
	split->quote = 0;
	split->bin = true;
	return (split);
}

t_words	*init_wc(void)
{
	t_words	*wc;

	wc = malloc((1) * sizeof(t_split));
	if (!wc)
	{
		// Need to check error code
		ft_printf("%s\n", "Error");
		exit(1);
	}
	wc->i = 0;
	wc->quote = 0;
	wc->c_words = 0;
	wc->bin = true;
	return (wc);
}
