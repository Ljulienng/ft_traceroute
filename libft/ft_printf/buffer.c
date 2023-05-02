/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:01:49 by jnguyen           #+#    #+#             */
/*   Updated: 2020/10/19 19:48:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		reset_buffer(t_pf *params)
{
	if (params->has_fd)
		params->ret += write(params->fd, params->str, params->pos);
	else
		params->ret += write(1, params->str, params->pos);
	params->pos = 0;
}

void		add_to_buffer(char c, t_pf *params)
{
	if (params->pos == BUFF_SIZE - 1)
		reset_buffer(params);
	params->str[params->pos++] = c;
}

int			is_flag(t_pf *params, char *charset)
{
	while (*charset)
	{
		if (*params->format == *charset)
			return (1);
		charset++;
	}
	return (0);
}
