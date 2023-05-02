/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 12:30:40 by julienngy         #+#    #+#             */
/*   Updated: 2019/11/26 14:11:18 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_set(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim2(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*s2;
	int		i;
	int		len;

	i = 0;
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (is_set(*start, set))
		start++;
	if (start < end)
		end--;
	while (is_set(*end, set))
		end--;
	len = end - start + 1;
	if (!(s2 = malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (len-- > 0)
		s2[i++] = *start++;
	s2[i] = '\0';
	return (s2);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char *s;

	if (!s1)
		return (NULL);
	else if (set[0] == '\0')
		return (ft_strdup(s1));
	s = ft_strtrim2(s1, set);
	return (s);
}
