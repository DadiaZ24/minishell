#include "minishell.h"

void	w_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
}

bool	check_max_min(char *str)
{
	long long	n;
	size_t		i;
	char		*str_n;

	i = 0;
	n = 0;
	i = ft_strlen(str);
	n = atoll(str);
	str_n = ft_lltoa(n);
	if (str[0] == '+')
		i--;
	ft_printf("str_n = %s\n", str_n);
	ft_printf("str_n = %d\n", ft_strlen(str_n));
	ft_printf("i = %d\n", i);
	if (ft_strlen(str_n) != i)
	{
		free(str_n);
		return (false);
	}
	free(str_n);
	return (true);
}

int	exit_builtin(int status, t_executor *exec, char **mtr)
{
	int i;

	i = -1;
	if (mtr[1])
	{
		if (mtr[2])
			return (set_exit_status(exec->shell, 1), w_error(" too many arguments\n"), 1);
		if (ft_strlen(mtr[1]) == 2 && mtr[1][0] == '-' && mtr[1][1] == '-')
		{
			free_process(exec);
			exit (0);
		}
		if (!check_max_min(mtr[1]))
		{
			set_exit_status(exec->shell, 2);
			w_error(" AAAAAAA numeric argument required\n");
			status = 2;
			return (1);
		}
		if (ft_strlen(mtr[1]) == 2 && mtr[1][0] == '+' && mtr[1][1] == '+')
		{
			set_exit_status(exec->shell, 2);
			w_error(" BBBBBB numeric argument required\n");
			status = 2;
			return (1);
		}
		if (mtr[1][0] == '-' || mtr[1][0] == '+')
			++i;
		while(mtr[1][++i])
		{
			if (!ft_isdigit(mtr[1][i]))
			{
				set_exit_status(exec->shell, 2);
				w_error(" CCCCCC numeric argument required\n");
				status = 2;
				return (1);
			}
		}
		status = ft_atoll(mtr[1]);
	}
	free_process(exec);
	exit(status % 256);
}
