#ifndef EXECUTOR_H
# define EXECUTOR_H

# ifndef MAX_PATH_LEN
#  define MAX_PATH_LEN 1024
# endif

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

void	pwd(void);
void	cd(t_token **tokens);
void	echo(t_token **tokens);

#endif