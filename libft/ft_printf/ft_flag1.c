/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:05:08 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/09 16:00:06 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_correct(t_pf *params)
{
	int i;

	i = 0;
	while (ft_isdigit(*params->format) || is_flag(params, "+-*."))
	{
		i++;
		params->format++;
	}
	if (is_flag(params, CONVERSIONS))
	{
		while (i)
		{
			i--;
			params->format--;
		}
		return (0);
	}
	while (i)
		i--;
	{
		params->format--;
	}
	add_to_buffer('%', params);
	return (1);
}

static void		parse_special_flags(t_pf *params)
{
	if (*params->format == '0' || *params->format == '-')
	{
		if (*params->format == '0')
			params->zero = 1;
		else if (*params->format == '-')
			params->minus = 1;
		params->format++;
		if (*params->format == '-')
		{
			params->minus = 1;
			params->format++;
		}
		if (params->minus == 1)
			params->zero = 0;
	}
}

static void		check_flags(t_pf *params)
{
	parse_special_flags(params);
	check_witdh(params);
	check_precision(params);
	if (params->precision < 0)
		params->has_precision = 0;
	if (params->min_width < 0)
	{
		params->minus = 1;
		params->min_width *= -1;
	}
	if (*params->format != '%')
		if (params->zero && (params->has_precision || params->minus))
			params->zero = 0;
}

static void		check_prct(t_pf *params)
{
	if (params->has_width && !params->minus && !params->zero &&\
		!params->has_precision)
		parse_space(params, params->min_width - 1, 0);
	else if (params->has_width && !params->minus && \
		(params->zero || \
		(params->has_precision && params->precision < params->min_width)))
		parse_space(params, params->min_width - 1, 1);
	else if (params->has_width && !params->minus && !params->zero &&\
		params->precision > params->min_width)
		parse_space(params, params->min_width - 1, 0);
	add_to_buffer('%', params);
	if (params->has_width && params->minus)
		parse_space(params, params->min_width - 1, 0);
}

void			parse_flags(t_pf *params)
{
	params->format++;
	if (!(check_correct(params)))
		check_flags(params);
	if (is_flag(params, CONVERSIONS))
	{
		*params->format == 'c' ? \
			c_to_buffer(params, va_arg(params->arg, int)) : 0;
		*params->format == 's' ? s_to_buffer(params) : 0;
		*params->format == 'd' ? int_to_buffer(params) : 0;
		*params->format == 'i' ? int_to_buffer(params) : 0;
		*params->format == 'p' ? hex_to_buffer(params) : 0;
		*params->format == 'u' ? unsigned_int_to_buffer(params) : 0;
		*params->format == 'x' ? unsigned_hex_to_buffer(params, 0) : 0;
		*params->format == 'X' ? unsigned_hex_to_buffer(params, 1) : 0;
		*params->format == '%' ? check_prct(params) : 0;
	}
	else
		c_to_buffer(params, *params->format);
	reset_flags(params);
}
