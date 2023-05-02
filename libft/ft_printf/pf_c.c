/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnguyen <jnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:05:25 by jnguyen           #+#    #+#             */
/*   Updated: 2019/12/16 14:00:46 by jnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		c_to_buffer(t_pf *params, char c)
{
	if (params->has_width && !params->minus && !params->noprint)
		parse_space(params, params->min_width - 1, 0);
	add_to_buffer(c, params);
	if (params->has_width && params->minus && !params->noprint)
		parse_space(params, params->min_width - 1, 0);
}
