#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!(str = (char *)malloc(size + 1)))
		return (NULL);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	str[size] = '\0';
	return (str);
}

