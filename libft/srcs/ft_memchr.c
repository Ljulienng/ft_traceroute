/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:33:39 by jnguyen           #+#    #+#             */
/*   Updated: 2019/11/26 14:10:36 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char *s;

	s = (unsigned char *)str;
	while (n)
	{
		if (*s == (unsigned char)c)
			return (s);
		else
			s++;
		n--;
	}
	return (NULL);
}
