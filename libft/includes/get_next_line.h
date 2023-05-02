/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienngy <julienngy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:27:26 by jnguyen           #+#    #+#             */
/*   Updated: 2020/02/02 22:22:32 by julienngy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

int		get_next_line(int fd, char **line);

#endif