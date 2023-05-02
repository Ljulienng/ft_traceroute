/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:10:36 by user42            #+#    #+#             */
/*   Updated: 2020/10/19 19:48:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	t_pf	params;

	params.format = (char *)format;
	if (!format)
		return (0);
	pf_init(&params);
	params.has_fd = 1;
	params.fd = fd;
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
