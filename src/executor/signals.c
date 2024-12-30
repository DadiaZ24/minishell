#include "minishell.h"

void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal(SIGINT, handle_sigint);
	}
}

void handle_sigquit(int sig)
{
	(void)sig;
}

void handle_eof(t_executor *exec)
{
	free_process(exec);
	write(1, "exit\n", 5);
	exit(0);
}

void signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
