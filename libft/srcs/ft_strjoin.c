/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:53:46 by julienngy         #+#    #+#             */
/*   Updated: 2019/10/16 14:58:29 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	if (!(s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (*s1)
	{
		s3[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		s3[i++] = *s2;
		s2++;
	}
	s3[i] = '\0';
	return (s3);
}
