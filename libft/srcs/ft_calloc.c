#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mal;

	mal = (void *)malloc(count * size);
	if (!mal)
		return (NULL);
	ft_bzero(mal, count * size);
	return (mal);
}
