/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:22:31 by julienngy         #+#    #+#             */
/*   Updated: 2019/11/21 16:15:05 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	y;

	i = start;
	y = 0;
	if (!s)
		return (NULL);
	if (!(str = malloc((int)len + 1)))
		return (NULL);
	while (s[i] && y < (unsigned int)len && start < ft_strlen(s))
	{
		str[y] = s[i];
		i++;
		y++;
	}
	str[y] = '\0';
	return (str);
}
