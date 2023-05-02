/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 00:04:31 by julienngy         #+#    #+#             */
/*   Updated: 2019/11/26 14:09:52 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*tab;

	if (!(tab = (char*)malloc(size * count)))
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
}
