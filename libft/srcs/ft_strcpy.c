#include "libft.h"

char *ft_strcpy(char *str)
{
	char *tmp;
	int i;

	i = 0;
	tmp = malloc(sizeof(ft_strlen(str) + 1));
	while (*str)
	{
		tmp[i++] = *str;
		str++;
	}
	tmp[i] = '\0';
	return (tmp);
}