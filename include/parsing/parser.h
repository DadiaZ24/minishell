/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:06:09 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/31 17:01:54 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define CMD_BIN	0
# define CMD_EVE	1
# define ARG		2
# define PIPE		3 
# define RED_OUT	4
# define RED_IN		5
# define APPEND		6
# define HERE_DOC	7

typedef struct s_token
{
	int				type;
	char			*info;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

char	**mini_split(char const *s);
void	lock_count(char **s, int *c_words, int *i, int *quote);
void	unlock_count(char **s, int *i);

#endif