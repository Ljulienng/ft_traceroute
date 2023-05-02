/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:26:06 by jnguyen           #+#    #+#             */
/*   Updated: 2019/11/26 14:11:33 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)str + i);
}
