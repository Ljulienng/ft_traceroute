/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:37:55 by jnguyen           #+#    #+#             */
/*   Updated: 2019/11/26 14:10:57 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *s, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && s[i])
		++i;
	return (i);
}

size_t			ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	len;

	len = ft_strnlen(dst, size);
	if (size > len)
		return (len + ft_strlcpy(dst + len, src, size - len));
	return (size + ft_strlen(src));
}
