/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:06:07 by jnguyen           #+#    #+#             */
/*   Updated: 2019/11/29 11:00:40 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_pf	params;

	params.format = (char *)format;
	if (!format)
		return (0);
	pf_init(&params);
	va_start(params.arg, format);
	while (*params.format)
	{
		if (*params.format == '%')
		{
			parse_flags(&params);
		}
		else
			add_to_buffer(*params.format, &params);
		params.format++;
	}
	va_end(params.arg);
	reset_buffer(&params);
	return (params.ret);
}
