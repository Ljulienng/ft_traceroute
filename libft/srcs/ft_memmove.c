/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:57:32 by jnguyen           #+#    #+#             */
/*   Updated: 2019/11/26 14:24:42 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	char	*end_s;
	char	*end_d;

	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		end_s = s + (len - 1);
		end_d = d + (len - 1);
		while (len--)
			*end_d-- = *end_s--;
	}
	return (dst);
}
