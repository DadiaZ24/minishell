#ifndef MINISHELL_H
# define MINISHELL_H

// Token Type
# define ARG		0
# define CMD		1
# define PIPE		2
# define D_PIPE		3 
# define RED_OUT	4
# define RED_IN		5
# define APPEND		6
# define HERE_DOC	7
# define MINI_FILE	8
# define MINI_EOF	9

//________________________________________________________________
//|_____________________________[LIBS]____________________________|
//|_______________________________________________________________|

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <bits/waitflags.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "parsing/parser.h"
# include "utils/utils.h"
# include "executor/executor.h"
# include "../libs/libft/ft_printf/ft_printf.h"
# include "../libs//libft/libft.h"
# include "../libs//libft/get_next_line/get_next_line_bonus.h"

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



//________________________________________________________________
//|__________________________[FUNCTIONS]__________________________|
//|_______________________________________________________________|

//Utils
int		minishell(t_executor *exec, char **envp);
int 	executor(t_executor *exec);
bool 	get_env(char **envp, t_shell *shell);
int		minishell_loop(t_executor *exec, t_token **tokens);


#endif