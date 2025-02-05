#include "libft.h"

long long	ft_atoll(const char *str)
{
	int			i;
	int			neg;
	long long	t;

	i = 0;
	neg = 1;
	t = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = t * 10 + (str[i] - '0');
		i++;
	}
	return (t * neg);
}
