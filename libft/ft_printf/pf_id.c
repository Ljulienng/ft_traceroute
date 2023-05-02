/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_id.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:02:19 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/09 16:00:37 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		num_len(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	while (n /= 10)
		i++;
	return (i + 1);
}

static void		int_to_buffer3(t_pf *params, char *n, int i)
{
	if (*n == '-' && !params->zero)
		add_to_buffer(n[i++], params);
	if (!(params->has_precision && !params->precision && *n == '0'))
	{
		while (n[i])
		{
			add_to_buffer(n[i], params);
			i++;
		}
	}
	free(n);
	if (params->precision > params->arg_len && params->minus)
		parse_space(params, params->min_width - params->precision, 0);
	else if (params->min_width > params->arg_len && params->minus)
		parse_space(params, params->min_width - params->arg_len, 0);
	else if (!params->precision && params->has_precision &&\
			!params->arg_len && params->minus)
		parse_space(params, params->min_width, 0);
}

static void		int_to_buffer2(t_pf *params, char *n)
{
	int i;

	i = 0;
	if (params->min_width > params->precision && !params->minus && \
		params->precision > params->arg_len)
		parse_space(params, params->min_width - params->precision, 0);
	else if (*n == '-' && params->precision == params->arg_len &&\
				params->min_width > params->precision)
		parse_space(params, params->min_width - params->precision, 0);
	if (*n == '-' && params->zero)
		add_to_buffer(n[i++], params);
	else if (*n == '-' && params->precision >= params->arg_len && !params->zero)
	{
		add_to_buffer(n[i], params);
		i++;
		params->arg_len--;
	}
	if (!params->minus)
		apply_parse_int(params, 0);
	else if (params->arg_len < params->precision)
		parse_space(params, params->precision - params->arg_len, 1);
	int_to_buffer3(params, n, i);
}

void			int_to_buffer(t_pf *params)
{
	char	*n;
	int		var;

	var = va_arg(params->arg, int);
	if (!(n = malloc(num_len(var) + 1)))
		return ;
	n = ft_itoa_id(var, n);
	params->arg_len = (int)ft_strlen((char *)n);
	if (params->has_precision && !params->precision && *n == '0')
		params->arg_len = 0;
	if (*n == '-' && params->precision >= params->arg_len && !params->zero)
		params->min_width--;
	int_to_buffer2(params, n);
}

void			apply_parse_int(t_pf *params, int i)
{
	if ((params->precision && params->min_width) > params->arg_len)
		return ;
	if (params->arg_len >= params->precision &&\
		params->arg_len <= params->min_width \
		&& !params->minus && params->has_precision)
		parse_space(params, params->min_width - params->arg_len, 0);
	else if (params->min_width > params->arg_len && params->zero &&\
		!params->has_precision)
		parse_space(params, params->min_width - params->arg_len, 1);
	else if (params->min_width > params->arg_len && !params->has_precision)
		parse_space(params, params->min_width - params->arg_len, 0);
	else if (i)
	{
		if (params->min_width > params->arg_len && params->has_precision && \
				params->precision < params->arg_len)
			parse_space(params, params->min_width - params->arg_len, 0);
		else if (params->min_width > params->precision && \
					params->precision > params->arg_len)
			parse_space(params, params->min_width - params->precision, 0);
	}
	if (params->precision > params->arg_len && params->has_precision)
		parse_space(params, params->precision - params->arg_len, 1);
}
