#include "libft.h"

void	ft_putmtr(char **mtr)
{
	int	i;

	i = -1;
	if (!mtr)
		return ;
	while (mtr[++i])
		ft_printf("index -> [%d]: %s\n", i, mtr[i]);
}
