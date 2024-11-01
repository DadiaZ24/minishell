#ifndef PARSER_H
# define PARSER_H

char	**mini_split(char const *s);
void	lock_count(char **s, int *c_words, int *i, int *quote);
void	unlock_count(char **s, int *i);

#endif