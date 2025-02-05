#include "minishell.h"

void	ft_print_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	while (temp)
	{
		printf("Info->[%s] || \tType->[%d]\n", temp->info, temp->type);
		temp = temp->next;
	}
	printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
}

char	*mini_fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

void	print_error(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
}

bool	get_env(char **envp, t_shell *shell)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		return (false);
	i = -1;
	while (envp[++i])
		shell->env[i] = ft_strdup(envp[i]);
	shell->env[i] = NULL;
	i = -1;
	return (true);
}
