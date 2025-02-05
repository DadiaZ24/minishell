#include "minishell.h"

void	set_exit_status(t_shell *shell, int status)
{
	shell->status = status;
}
