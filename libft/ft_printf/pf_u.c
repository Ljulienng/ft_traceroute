/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:02:31 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/07 11:54:21 by jnguyen          ###   ########.fr       */
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

static void		unsigned_int_to_buffer2(t_pf *params, char *n)
{
	int i;

	i = 0;
	if (!(params->has_precision && !params->precision && *n == '0'))
	{
		while (n[i])
		{
			add_to_buffer(n[i], params);
			i++;
		}
	}
	free(n);
	if (params->min_width > params->precision && params->minus\
		&& params->arg_len >= params->precision)
		parse_space(params, params->min_width - params->arg_len, 0);
	else if (params->min_width > params->precision && params->minus\
		&& params->arg_len < params->precision)
		parse_space(params, params->min_width - params->precision, 0);
}

void			unsigned_int_to_buffer(t_pf *params)
{
	char		*n;
	long int	var;

	var = va_arg(params->arg, int);
	if (!(n = malloc(num_len((unsigned int)var, 10) + 1)))
		return ;
	n = ft_unsigned_itoa(var, n);
	params->arg_len = (int)ft_strlen((char *)n);
	if (!params->precision && *n == '0' && params->has_precision)
		params->arg_len = 0;
	if (!params->minus)
		apply_parse_int(params, 1);
	else if (params->precision > params->arg_len && params->has_precision \
			&& params->minus)
		parse_space(params, params->precision - params->arg_len, 1);
	unsigned_int_to_buffer2(params, n);
}
