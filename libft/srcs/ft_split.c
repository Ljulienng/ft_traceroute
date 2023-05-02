/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:37:39 by jnguyen           #+#    #+#             */
/*   Updated: 2019/10/29 10:52:30 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_count(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static int			ft_size(char const *str, char c)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

static void			*ft_free(char **str)
{
	while (*str)
	{
		free(str);
		str++;
	}
	return (NULL);
}

static char			**ft_strsplit(char const *str, char c)
{
	char	**s;
	int		i;
	int		j;
	int		k;
	int		words;

	words = ft_count(str, c);
	i = -1;
	k = 0;
	if (!(s = (char **)malloc((words + 1) * sizeof(char *))))
		return (NULL);
	while (++i < words && !(j = 0))
	{
		if (!(s[i] = (char *)malloc(ft_size(&str[k], c) + 1)))
			return (ft_free(s));
		while (str[k] == c)
			k++;
		while (str[k] != c && str[k])
			s[i][j++] = str[k++];
		s[i][j] = '\0';
	}
	s[i] = 0;
	return (s);
}

char				**ft_split(char const *str, char c)
{
	char	**s;

	if (!str)
		return (NULL);
	s = ft_strsplit(str, c);
	return (s);
}
