#include "minishell.h"

void	lock_count(char **s, int *c_words, int *i, int *quote, bool *bin)
{
	if (ft_pipe_or_redirect(*s) > 0 && *i == 0)
	{
		if (ft_pipe_or_redirect(*s) == 2)
			(*s)++;
		*c_words += 1;
		*bin = true;
	}
	else if (ft_isquote(**s) > 0 && *i == 0 && (**s + 1) != 0)
	{
		*quote = ft_isquote(**s);
		if (*bin)
		{
			*c_words += 1;
			*bin = false;
		}
		(*s)++;
		while (ft_isquote(**s) != *quote && **s != 0)
			(*s)++;
	}
	else if (!ft_iswhitespc(**s) && *i == 0)
	{
		*i = 1;
		*c_words += 1;
		*bin = true;
	}
}

void	unlock_count(char **s, int *i, bool *bin)
{
	if (ft_iswhitespc(**s) || ft_pipe_or_redirect(*s) > 0)
	{
		*i = 0;
		*bin = true;
	}
}

int	mini_words(char const *s)
{
	int		i;
	int		quote;
	int		c_words;
	bool	bin;

	i = 0;
	quote = 0;
	c_words = 0;
	bin = true;
	while (*s)
	{
		lock_count((char **)&s, &c_words, &i, &quote, &bin);
		s++;
		unlock_count((char **)&s, &i, &bin);
	}
	return (c_words);
}
