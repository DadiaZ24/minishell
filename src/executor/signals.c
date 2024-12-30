#include "minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	write(1, "minishell$ ", 11);
}

void handle_sigquit(int sig)
{
	(void)sig;
}

void signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}
