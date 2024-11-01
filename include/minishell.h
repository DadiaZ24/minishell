#ifndef MINISHELL_H
# define MINISHELL_H

// Token Type
# define CMD_BIN	0
# define CMD_EVE	1
# define ARG		2
# define PIPE		3 
# define RED_OUT	4
# define RED_IN		5
# define APPEND		6
# define HERE_DOC	7

//________________________________________________________________
//|_____________________________[LIBS]____________________________|
//|_______________________________________________________________|

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parsing/parser.h"
# include "utils/utils.h"
# include "executor/executor.h"
# include "../libs/libft/ft_printf/ft_printf.h"
# include "../libs//libft/libft.h"
# include "../libs//libft/get_next_line/get_next_line_bonus.h"
# include <stdbool.h>

//________________________________________________________________
//|____________________________[MACROS]___________________________|
//|_______________________________________________________________|

//----COLORS
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define BLUE "\033[0;36m"
# define DEFAULT_COLOR "\033[0m"

//-----MESSAGES


//________________________________________________________________
//|__________________________[STRUCTURES]_________________________|
//|_______________________________________________________________|

typedef struct s_token
{
	int				type;
	char			*info;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	char	*line;
} t_shell;

//________________________________________________________________
//|__________________________[FUNCTIONS]__________________________|
//|_______________________________________________________________|

void	minishell(t_token **tokens);

//Utils
int	minishell(t_shell *shell, t_token **tokens, char **envp);

void	free_tokens(t_token **tokens);

#endif