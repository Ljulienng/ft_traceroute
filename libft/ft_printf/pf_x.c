/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:02:43 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/07 11:51:55 by jnguyen          ###   ########.fr       */
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

static void		unsigned_hex_to_buffer2(t_pf *params, char *n)
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
	if (!params->precision && params->has_precision && \
		!params->arg_len && params->has_width && params->minus)
		parse_space(params, params->min_width, 0);
	else if (params->min_width > params->precision && params->minus \
		&& params->has_width && params->arg_len < params->precision)
		parse_space(params, params->min_width - params->precision, 0);
	else if (params->min_width > params->arg_len && params->minus &&\
		params->precision <= params->arg_len)
		parse_space(params, params->min_width - params->arg_len, 0);
}

void			unsigned_hex_to_buffer(t_pf *params, int x)
{
	char		*n;
	long int	var;

	var = va_arg(params->arg, unsigned int);
	if (!(n = malloc(num_len(var, 16) + 1)))
		return ;
	if (x == 0)
		n = fill_itoa_base(var, 16, 0, n);
	else
		n = fill_itoa_base(var, 16, 1, n);
	params->arg_len = (int)ft_strlen((char *)n);
	if (params->has_precision && params->precision == 0 && *n == '0')
		params->arg_len = 0;
	apply_parse_hex(params);
	unsigned_hex_to_buffer2(params, n);
}

void			apply_parse_hex(t_pf *params)
{
	if (!params->minus)
	{
		if (params->has_precision && params->has_width && \
				params->arg_len < params->min_width && \
					params->arg_len > params->precision)
			parse_space(params, params->min_width - params->arg_len, 0);
		else if (params->precision >= params->arg_len && params->has_width && \
				params->has_precision < params->min_width)
			parse_space(params, params->min_width - params->precision, 0);
		else if (params->has_width && params->min_width > params->arg_len \
			&& !params->has_precision)
			parse_space(params, params->min_width - params->arg_len, 0);
		else if (!params->precision && !params->arg_len &&\
				params->has_precision\
				&& params->has_width)
			parse_space(params, params->min_width, 0);
		if (params->precision > params->arg_len)
			parse_space(params, params->precision - params->arg_len, 1);
	}
	else if (params->has_precision)
		if (params->precision > params->arg_len)
			parse_space(params, params->precision - params->arg_len, 1);
}
