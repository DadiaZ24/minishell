/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:40:08 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:40:08 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void		free_mtr(char **mtr);
void		free_token(t_token *token);
char		**free_split(char **str, int j);
void		free_d(t_executor *exec);
void		free_all(t_executor	*exec);
void		free_process(t_executor *exec);
void		ft_free_cmds(t_cmds *cmds);

void		create_token(char **mtr, t_token **token);
t_split		*init_split_var(void);
t_words		*init_wc(void);
t_executor	*init_exec(t_executor *exec);
t_exp		*init_exp(t_exp	*exp, t_token **token);

void		ft_print_token(t_token **token);
void		print_error(char *str);
char		*mini_fill_word(const char *str, int start, int end);

char		*cmd_path(t_executor *exec, char *cmd);

void		wait_pid(t_executor *exec);
bool		handle_redirects(t_executor *exec, t_cmds *cmds);
bool		handle_heredoc(t_cmds *cmds);
bool		find_heredoc(t_cmds **cmds);
bool		check_signal(int i);

bool		check_permission(t_executor *exec, char *path, int i);
void		exit_exec(t_executor *exec, t_cmds *cmds);
void		exit_exec2(t_executor *exec, t_cmds *cmds);
void		error_check(t_executor *exec, t_cmds *cmds);
void		w_error(char *str);

#endif