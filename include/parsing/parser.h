#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_split
{
	size_t	i;
	int		j;
	int		s_word;
	int		quote;
	bool	bin;
}	t_split;

typedef struct s_words
{
	int		i;
	int		quote;
	int		c_words;
	bool	bin;
}	t_words;

char	**mini_split(char const *s);
char	**mini_makesplit(char const *s, char **lst_str);
int		mini_words(char const *s);
void	lock_count(char **s, t_words *wc);
void	unlock_count(char **s, t_words *wc);

#endif