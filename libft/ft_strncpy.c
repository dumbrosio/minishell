#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	char	*runner;

	i = 0;
	runner = dest;
	while (*src && i < n)
	{
		*runner++ = *src++;
		i++;
	}
	*runner = '\0';
	while (i < n)
	{
		*runner++ = '\0';
		i++;
	}
	return (dest);
}