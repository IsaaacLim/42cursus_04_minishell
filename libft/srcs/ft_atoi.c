#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		flag;
	long	tot;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	flag = 1;
	if (str[i] == '-')
	{
		flag *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	tot = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tot = tot * 10 + (str[i] - '0');
		i++;
	}
	return (tot * (long)flag);
}
