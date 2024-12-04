#include "libft.h"

void	ft_putmtr(char **mtr)
{
	int	i;

	i = -1;
	if (!mtr)
		return ;
	while (mtr[++i])
	{
		printf("%s", mtr[i]);
		if (mtr[i + 1])
			printf(" ");
	}
}
