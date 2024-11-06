#include "libft.h"

void	ft_putmtr(char **mtr)
{
	int	i;

	i = -1;
	if (!mtr)
		return ;
	while (mtr[++i])
	{
		ft_v_putstr(mtr[i]);
		ft_v_putchar('\n');
	}
}
