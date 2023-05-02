/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:19:55 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/07 14:08:01 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	num_len(uintptr_t n, int base)
{
	size_t i;

	i = 0;
	while (n /= base)
		i++;
	return (i + 1);
}

static int		num_len2(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	while (n /= 10)
		i++;
	return (i + 1);
}

char			*fill_itoa_base(long int i, int base, int x, char *n)
{
	char		*baselist;
	size_t		len;
	uintptr_t	num;

	num = (uintptr_t)i;
	len = num_len(num, base) + 1;
	if (x == 0)
		baselist = "0123456789abcdef";
	else
		baselist = "0123456789ABCDEF";
	n[--len] = '\0';
	if (!num)
		n[--len] = baselist[0];
	while (num)
	{
		n[--len] = baselist[num % base];
		num = num / base;
	}
	return (n);
}

char			*ft_unsigned_itoa(int n, char *num)
{
	size_t			len;
	long int		i;

	i = (unsigned int)n;
	len = num_len(i, 10) + 1;
	num[--len] = '\0';
	if (!n)
		num[--len] = '0';
	while (i)
	{
		num[--len] = i % 10 + '0';
		i /= 10;
	}
	return (num);
}

char			*ft_itoa_id(int n, char *num)
{
	int				len;
	unsigned int	i;

	i = n;
	len = num_len2(n) + 1;
	if (n < 0)
	{
		num[0] = '-';
		i = n * -1;
	}
	num[--len] = '\0';
	if (n == 0)
		num[--len] = '0';
	while (i)
	{
		num[--len] = i % 10 + '0';
		i /= 10;
	}
	return (num);
}
