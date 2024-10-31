/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:16:57 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/31 17:22:00 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"
# include "utils.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "libft/get_next_line/get_next_line_bonus.h"

void	minishell(t_token **tokens);

#endif