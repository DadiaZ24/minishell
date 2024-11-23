#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_mtr(char **mtr);
void	free_token(t_token **token);
char	**free_split(char **str, int j);

void	create_token(char **mtr, t_token **token);
void	create_ast(t_token **token, t_ast **ast);
t_ast	*init_ast(t_ast	*ast);
t_split	*init_split_var(void);
t_words	*init_wc(void);

void	ft_print_ast(t_ast *ast);
void	ft_print_token(t_token **token);
char	*mini_fill_word(const char *str, int start, int end);

#endif