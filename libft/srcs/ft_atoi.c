/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:38:37 by jnguyen           #+#    #+#             */
/*   Updated: 2019/10/29 14:27:53 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	int				num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' ||
				str[i] == '\r' || str[i] == ' ' || str[i] == '\f'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}
