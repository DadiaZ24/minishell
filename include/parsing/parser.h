#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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

typedef struct s_token
{
	int				type;
	char			*info;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_ast
{
	int				type;
	char			*red_target;
	char			**arg;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
}	t_ast;

typedef struct s_ast_utils
{
	int		i;
	t_token	*temp;
	t_token	*branch;
	t_ast	*ast_temp;
}	t_ast_utils;

typedef struct s_shell
{
	char	*line;
	int		status;
	char	**env;

}	t_shell;

typedef struct s_executor
{
	t_ast 	**ast;
	t_shell	*shell;
	t_token	**token;
	int		fd_in;
	int		fd_out;
	int		*pid;
	int		num_pipe;
	bool	is_child;
} t_executor;

t_ast_utils	*init_au(t_token **token, t_ast **ast);

char		**mini_split(char const *s);
char		**mini_makesplit(char const *s, char **lst_str);
int			mini_words(char const *s);
void		lock_count(char **s, t_words *wc);
void		unlock_count(char **s, t_words *wc);
void		lexer(t_token **tokens);
int			check_redirect_or_pipe(char *s);
int			check_file_eof(char *s);

#endif