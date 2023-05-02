/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:00:45 by jnguyen           #+#    #+#             */
/*   Updated: 2020/10/19 19:21:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include <inttypes.h>

# define CONVERSIONS "cspdiuxX%"
# define ALL_FLAGS "cspdiuxX*-.0C"
# define BUFF_SIZE 64

typedef struct	s_pf
{
	char	str[BUFF_SIZE];
	char	*format;
	char	*flags;
	int		has_fd;
	int		fd;
	int		ret;
	int		min_width;
	int		has_width;
	int		zero;
	int		minus;
	int		arg_len;
	int		right_pad;
	int		precision;
	int		has_precision;
	int		pos;
	int		noprint;
	int		null;
	va_list arg;
}				t_pf;

int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);


void			reset_buffer(t_pf *params);
void			add_to_buffer(char c, t_pf *params);
void			s_to_buffer(t_pf *params);
void			c_to_buffer(t_pf *params, char c);
void			after_parse(t_pf *params);

void			hex_to_buffer(t_pf *params);
void			unsigned_int_to_buffer(t_pf *params);
void			unsigned_hex_to_buffer(t_pf *params, int x);
void			int_to_buffer(t_pf *params);

void			pf_init(t_pf *buf);
void			reset_flags(t_pf *params);

void			ft_print_buffer(char *str, int pos);

void			parse_flags(t_pf *params);
int				is_flag(t_pf *params, char *charset);
void			define_flags(t_pf *params);

char			*fill_itoa_base(long int i, int base, int x, char *n);
char			*ft_unsigned_itoa(int n, char *num);
char			*ft_itoa_id(int n, char *num);

void			check_witdh(t_pf *params);
void			parse_space(t_pf *params, int to_parse, int is_int);
void			apply_parse(t_pf *params, int i);
void			apply_parse_hex(t_pf *params);
void			apply_parse_int(t_pf *params, int i);

void			find_flags(t_pf *params);

void			check_precision(t_pf *params);

#endif
