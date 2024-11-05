#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

char	**mini_split(char const *s);
int		ft_words(char const *s);
void	lock_count(char **s, int *c_words, int *i, int *quote, bool *bin);
void	unlock_count(char **s, int *i, bool *bin);

#endif