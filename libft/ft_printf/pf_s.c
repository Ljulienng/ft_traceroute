/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:02:55 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/07 14:07:49 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		s_to_buffer3(t_pf *params)
{
	if (!params->minus)
		return ;
	if (!params->precision && params->has_precision &&\
		!params->null && !params->arg_len)
		parse_space(params, params->min_width, 0);
	else if (params->arg_len < params->min_width && params->has_precision\
			&& params->precision <= params->arg_len && !params->null)
		parse_space(params, params->min_width - params->precision, 0);
	else if (params->arg_len < params->min_width &&\
			params->precision > params->arg_len && !params->null)
		parse_space(params, params->min_width - params->arg_len, 0);
	else if (params->has_width && !params->null && !params->arg_len)
		parse_space(params, params->min_width - params->arg_len, 0);
	else if (params->has_width && !params->null && \
			params->has_precision && params->precision)
		parse_space(params, params->min_width - params->precision, 0);
	else if (params->has_width && !params->has_precision && !params->null)
		parse_space(params, params->min_width - params->arg_len, 0);
	after_parse(params);
}

static void		s_to_buffer2(t_pf *params, char *str, int i)
{
	if (params->null && i < 6 && params->has_width \
		&& !params->minus && params->has_precision)
		parse_space(params, params->min_width - params->precision, 0);
	else if (params->null && i > 6 && params->has_width \
		&& !params->minus && params->precision < params->arg_len)
		parse_space(params, params->min_width - i, 0);
	else if (params->null && i == 6 && params->has_width \
		&& !params->minus && params->precision == params->arg_len)
		parse_space(params, params->min_width - i, 0);
	else if (!params->minus)
		apply_parse(params, i);
	while (*str && !params->noprint)
	{
		add_to_buffer(*str, params);
		if (params->has_precision && i--)
			if (i == 0)
				break ;
		str++;
	}
	s_to_buffer3(params);
}

void			s_to_buffer(t_pf *params)
{
	char	*str;
	int		i;

	i = params->precision;
	str = va_arg(params->arg, char *);
	if (str == NULL)
	{
		str = "(null)";
		params->null = 1;
	}
	params->arg_len = (int)ft_strlen((char *)str);
	if ((!params->arg_len || (!params->precision && params->has_precision))\
		&& params->has_width)
	{
		parse_space(params, params->min_width, 0);
		return ;
	}
	s_to_buffer2(params, str, i);
}

void			after_parse(t_pf *params)
{
	if (params->null)
	{
		if (params->has_width && params->has_precision)
		{
			if (params->noprint)
				parse_space(params, params->min_width, 0);
			else if (params->precision < 6)
				parse_space(params, params->min_width - params->precision, 0);
			else if (params->precision == 6)
				parse_space(params, params->min_width - params->arg_len, 0);
			else if (params->precision > params->arg_len && \
				params->arg_len < params->min_width)
				parse_space(params, params->min_width - params->arg_len, 0);
		}
		else
		{
			if (params->has_width && params->min_width > params->arg_len)
				parse_space(params, params->min_width - params->arg_len, 0);
		}
	}
}
