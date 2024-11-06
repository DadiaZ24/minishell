#ifndef UTILS_H
# define UTILS_H

typedef struct s_token
{
	int				type;
	char			*info;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	free_mtr(char **mtr);
void	free_token(t_token **token);
char	**free_split(char **str, int j);

void	create_token(char **mtr, t_token **token);

void	ft_print_token(t_token **token);

#endif