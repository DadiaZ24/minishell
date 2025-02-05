#include "libft.h"

void	ft_v_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_v_putchar(s[i]);
		i++;
	}
}
