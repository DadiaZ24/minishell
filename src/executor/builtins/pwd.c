/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:43:45 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:43:45 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **mtr, t_executor *exec)
{
	char	cwd[MAX_PATH_LEN];

	(void)mtr;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		printf("ERROR READING PWD\n");
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	else
		return (set_exit_status(exec->shell, 0), 1);
	return (set_exit_status(exec->shell, 0), 1);
}
