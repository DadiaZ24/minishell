#include "minishell.h"

bool env(t_shell *shell, t_token **tokens)
{
	int i;

	(void)tokens;
	update_env(shell);
	i = -1;
	if ((*tokens)->next)
		return (printf("env: can not receive arguments or options (imposed by subject)\n"), false);
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	return (true);
}

void update_env(t_shell *shell)
{
	int i;
	int j;

	i = -1;
	while (shell->env[++i])
	{
		j = -1;
		while(shell->export[++j])
		{
			if (ft_strncmp(shell->env[i], shell->export[j], ft_strclen(shell->export[j], '=') + 1) == 0)
			{
				shell->env[i] = shell->export[j];
				break;
			}
		}
	}
}