#include "minishell.h"

int	ft_words(char const *s)
{
	int	i;
	int	quote;
	int	c_words;

	i = 0;
	quote = 0;
	c_words = 0;
	while (*s)
	{
		lock_count(&s, &c_words, &i, &quote);
		unlock_count(&s, &i);
		s++;
	}
	return (c_words);
}

char	*fill_word(const char *str, int start, int end)
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

char	**ft_free(char **str, int j)
{
	while (j--)
		free(str[j]);
	free(str);
	return (NULL);
}

// INCOMPLETE, NEED TO COMPLETE SPLIT
// INCOMPLETE, NEED TO COMPLETE SPLIT
// INCOMPLETE, NEED TO COMPLETE SPLIT
// INCOMPLETE, NEED TO COMPLETE SPLIT
char	**ft_makesplit(char const *s, char **lst_str)
{
	size_t	i;
	int		j;
	int		s_word;

	i = -1;
	j = 0;
	s_word = -1;
	while (++i <= ft_strlen(s))
	{
		if (!ft_iswhitespc(s[i] && ft_pipe_or_redirect == 0
			&& ft_isquote == 0) && s_word < 0)
			s_word = i;
		else if ((ft_iswhitespc(s[i] && ft_pipe_or_redirect > 0
			&& ft_isquote > 0) || i == ft_strlen(s)) && s_word >= 0)
		{
			lst_str[j] = fill_word(s, s_word, i);
			if (!(lst_str[j]))
				return (ft_free(lst_str, j));
			s_word = -1;
			j++;
		}
	}
	lst_str[j] = NULL;
	return (lst_str);
}

char	**mini_split(char const *s)
{
	char	**lst_str;

	if (!s)
		return (NULL);
	lst_str = malloc((ft_words(s) + 1) * sizeof(char *));
	if (!lst_str)
		return (NULL);
	lst_str = ft_makesplit(s, lst_str);
	return (lst_str);
}
