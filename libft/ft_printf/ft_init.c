/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:05:58 by jnguyen           #+#    #+#             */
/*   Updated: 2020/10/19 18:33:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_init(t_pf *params)
{
	(void)params;
	params->zero = 0;
	params->minus = 0;
	params->has_width = 0;
	params->min_width = 0;
	params->has_precision = 0;
	params->precision = 0;
	params->pos = 0;
	params->ret = 0;
	params->noprint = 0;
	params->null = 0;
	params->has_fd = 0;
}

void	reset_flags(t_pf *params)
{
	params->zero = 0;
	params->minus = 0;
	params->has_width = 0;
	params->min_width = 0;
	params->has_precision = 0;
	params->precision = 0;
	params->noprint = 0;
	params->null = 0;
}
