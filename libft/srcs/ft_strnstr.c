/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:48:22 by jnguyen           #+#    #+#             */
/*   Updated: 2019/11/26 14:11:05 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = 0;
	k = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] && k < len)
	{
		while (haystack[i] && haystack[i] == needle[j] && (k + i) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char*)haystack + i - j);
			i++;
			j++;
		}
		i = 0;
		j = 0;
		haystack++;
		k++;
	}
	return (NULL);
}
