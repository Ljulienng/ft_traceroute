/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:00:31 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/07 13:58:50 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_witdh(t_pf *params)
{
	if ((*params->format == '*' || ft_isdigit(*params->format)) \
		&& !params->has_width)
	{
		if (*params->format == '*')
		{
			params->has_width = 1;
			params->min_width = 0;
			params->format++;
			params->min_width = va_arg(params->arg, int);
		}
		else if (ft_isdigit(*params->format))
		{
			params->has_width = 1;
			params->min_width = 0;
			while (ft_isdigit(*params->format))
				params->min_width = params->min_width * 10 + \
					(*(params->format++) - '0');
		}
	}
}

void	parse_space(t_pf *params, int to_parse, int is_int)
{
	int	i;

	i = 0;
	while (i < to_parse)
	{
		if (params->zero || is_int)
			add_to_buffer('0', params);
		else
			add_to_buffer(' ', params);
		i++;
	}
}

void	apply_parse(t_pf *params, int i)
{
	if (params->has_precision && params->has_width && !params->null)
	{
		if (params->min_width > params->precision &&\
			params->arg_len > params->precision)
			parse_space(params, params->min_width - params->precision, 0);
		else if (params->min_width > params->precision && !params->precision)
			parse_space(params, params->min_width, 0);
		else if (params->min_width > params->arg_len)
			parse_space(params, params->min_width - params->arg_len, 0);
	}
	else if (params->has_width && !params->has_precision)
	{
		if (params->arg_len < params->min_width && !params->null)
			parse_space(params, params->min_width - params->arg_len, 0);
		else if (params->arg_len < params->min_width && params->null &&\
			params->min_width >= 6)
			parse_space(params, params->min_width - params->arg_len, 0);
		else if (params->min_width > 1 && !params->arg_len)
			parse_space(params, params->min_width, 0);
	}
	if (params->null && i > 6 && params->has_width \
		&& params->precision > params->arg_len)
		parse_space(params, params->min_width - params->arg_len, 0);
}
