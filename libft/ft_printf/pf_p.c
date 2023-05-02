/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:55:45 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/07 15:38:02 by jnguyen          ###   ########.fr       */
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

static void		hex_to_buffer2(t_pf *params, char *n)
{
	int i;

	i = 0;
	if (params->min_width > params->arg_len && !params->minus)
		parse_space(params, params->min_width - params->arg_len, 0);
	add_to_buffer('0', params);
	add_to_buffer('x', params);
	while (n[i] && !params->has_precision)
	{
		add_to_buffer(n[i], params);
		i++;
	}
	free(n);
	if (params->min_width > params->arg_len && params->minus)
		parse_space(params, params->min_width - params->arg_len, 0);
}

void			hex_to_buffer(t_pf *params)
{
	char		*n;
	uintptr_t	var;

	var = va_arg(params->arg, uintptr_t);
	if (!(n = malloc(num_len(var, 16) + 1)))
		return ;
	n = fill_itoa_base(var, 16, 0, n);
	params->arg_len = (int)ft_strlen(n) + 2;
	if (params->has_precision)
		params->arg_len -= 1;
	hex_to_buffer2(params, n);
}
