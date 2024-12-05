#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void		free_mtr(char **mtr);
void		free_token(t_token **token);
char		**free_split(char **str, int j);
void		free_ast(t_ast **ast);
void		free_d(t_executor *exec);
void		free_all(t_executor	*exec);
void		free_process(t_executor *exec);

void		create_token(char **mtr, t_token **token);
void		create_ast(t_token **token, t_ast **ast);
t_ast		*ast_node(t_token *start, t_token *end, t_ast *ast);
t_ast		*init_ast(t_ast	*ast);
t_split		*init_split_var(void);
t_words		*init_wc(void);
t_executor	*init_exec(t_executor *exec);
t_exp		*init_exp(t_exp	*exp, t_token **token);

void		ft_print_ast(t_ast *ast);
void		ft_print_token(t_token **token);
void		print_error(char *str);
char		*mini_fill_word(const char *str, int start, int end);

void		ast_utils_else(t_ast_utils *au, t_ast **ast);
void		ast_utils_other_than_pipe(t_ast_utils *au, t_ast **ast);
void		ast_utils_pipe(t_ast_utils *au, t_ast **ast);
void		ast_utils_red(t_ast_utils *au, t_ast **ast);

void		wait_pid(t_executor *exec);
void		handle_redirects(t_executor *exec, t_ast *ast);
void		check_permission(t_executor *exec, char *path, int i);
void		exit_exec(t_executor *exec, t_ast *ast);

#endif