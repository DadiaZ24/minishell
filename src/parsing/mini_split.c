#include "minishell.h"

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

char	**mini_makesplit(char const *s, char **lst_str)
{
	size_t	i;
	int		j;
	int		s_word;
	int		quote;
	bool	bin;

	i = -1;
	j = 0;
	s_word = -1;
	quote = 0;
	bin = true;
	while (++i <= ft_strlen(s))
	{
		if (ft_pipe_or_redirect((char *)&s[i]) > 0 && s_word < 0)
		{
			s_word = i;
			if (ft_strncmp(&s[i], &s[i + 1], 1) == 0)
				++i;
			lst_str[j] = mini_fill_word(s, s_word, i + 1);
			if (!(lst_str[j]))
				return (free_split(lst_str, j));
			s_word = -1;
			bin = true;
			j++;
		}
		else if (ft_isquote(s[i]) > 0 && s[i + 1] != 0)
		{
			quote = ft_isquote(s[i]);
			if (bin)
			{
				s_word = i;
				bin = false;
			}
			++i;
			while (ft_isquote(s[i]) != quote && s[i] != 0)
				++i;
		}
		else if (!ft_iswhitespc(s[i]) && s_word < 0)
		{
			s_word = i;
			bin = true;
		}
		else if ((ft_iswhitespc(s[i]) || ft_pipe_or_redirect((char *)&s[i]) > 0 || i == ft_strlen(s)) && s_word >= 0)
		{
			lst_str[j] = mini_fill_word(s, s_word, i);
			if (!(lst_str[j]))
				return (free_split(lst_str, j));
			s_word = -1;
			bin = true;
			j++;
			if (ft_pipe_or_redirect((char *)&s[i]) > 0)
				--i;
		}
	}
	lst_str[j] = NULL;
	return (lst_str);
}

char	**mini_split(char const *s)
{
	char	**mtr;

	if (!s)
		return (NULL);
	mtr = malloc((mini_words(s) + 1) * sizeof(char *));
	if (!mtr)
		return (NULL);
	mtr = mini_makesplit(s, mtr);
	return (mtr);
}
