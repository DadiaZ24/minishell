#include "libft.h"

void	ft_putmtr(char **mtr)
{
	int	i;

	i = -1;
	if (!mtr)
		return ;
	while (mtr[++i])
	{
		ft_printf("%s", mtr[i]);
		if (mtr[i + 1])
			ft_printf(" ");
	}
}
