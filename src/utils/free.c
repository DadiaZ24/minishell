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
