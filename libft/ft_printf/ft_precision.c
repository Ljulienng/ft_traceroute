/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:41:40 by jnguyen           #+#    #+#             */
/*   Updated: 2020/01/07 14:08:09 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_precision(t_pf *params)
{
	if (*params->format == '.' && !params->has_precision)
	{
		params->has_precision = 1;
		params->format++;
		if (ft_isdigit(*params->format))
		{
			params->has_precision = 1;
			params->precision = 0;
			while (ft_isdigit(*params->format))
				params->precision = params->precision * 10 + \
					(*(params->format++) - '0');
		}
		else if (*params->format == '*')
		{
			params->has_precision = 1;
			params->precision = 0;
			params->format++;
			params->precision = va_arg(params->arg, int);
		}
		if (params->precision == 0)
			params->noprint = 1;
		else
			params->noprint = 0;
	}
}
