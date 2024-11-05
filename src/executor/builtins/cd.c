#include "minishell.h"

void	cd(t_token **tokens)
{
	char	current_path[MAX_PATH_LEN];

	if (getcwd(current_path, sizeof(current_path)))
	{
		if ((*tokens)->next->info)
		{
			if (!chdir(ft_joinpath(current_path, (*tokens)->next->info)))
				printf("AHAHAHAHAHAH MAMA BOI!!!\n\n");
			else
				printf("ESTE MINISHELL É MESMO CABRAO!!!");
		}
		else
			printf("TO DO!");
	}
}
