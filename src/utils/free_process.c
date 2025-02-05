/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:49 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:49 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_d(t_executor *exec)
{
	free_mtr(exec->shell->env);
	free(exec->cmds);
	free(exec->shell);
	free(exec->token);
	free(exec);
}

void	free_all(t_executor *exec)
{
	free(exec->shell->line);
	ft_free_cmds(*exec->cmds);
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
}

void	free_process(t_executor *exec)
{
	free_all(exec);
	free_d(exec);
}
