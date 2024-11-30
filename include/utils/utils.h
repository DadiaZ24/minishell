#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_mtr(char **mtr);
void	free_token(t_token **token);
char	**free_split(char **str, int j);
void	free_ast(t_ast **ast);
void	free_all(char **mtr, char *line, t_token **tokens, t_ast **ast);

void	create_token(char **mtr, t_token **token);
void	create_ast(t_token **token, t_ast **ast);
t_ast	*ast_node(t_token *start, t_token *end, t_ast *ast);
t_ast	*init_ast(t_ast	*ast);
t_split	*init_split_var(void);
t_words	*init_wc(void);

void	ft_print_ast(t_ast *ast);
void	ft_print_token(t_token **token);
char	*mini_fill_word(const char *str, int start, int end);

void	ast_utils_else(t_ast_utils *au, t_ast **ast);
void	ast_utils_other_than_pipe(t_ast_utils *au, t_ast **ast);
void	ast_utils_pipe(t_ast_utils *au, t_ast **ast);
void	ast_utils_red(t_ast_utils *au, t_ast **ast);

#endif