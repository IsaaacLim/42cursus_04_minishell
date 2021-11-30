#include "libft.h"

/*
** strjoin used to add a character (char c) in between s1 & s2
** to avoid calling strjoin twice
** - used to join path variable with '/'
** - used to join environment varible with '=
*/
char	*ft_strjoin2(char const *s1, char const *s2, char c)
{
	int		len;
	int		i;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = malloc(sizeof(char) * (len + 1 + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (*s1)
		tmp[i++] = *s1++;
	tmp[i++] = c;
	while (*s2)
		tmp[i++] = *s2++;
	tmp[i] = '\0';
	return (tmp);
}
