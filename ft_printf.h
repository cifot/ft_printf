/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 09:26:05 by nharra            #+#    #+#             */
/*   Updated: 2019/09/23 12:29:17 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef enum	e_flags {
				flag_plus = 1,
				flag_minus = 2,
				flag_space = 4,
				flag_zero = 8,
				flag_hash = 16
}				t_flags;

typedef enum	e_size_type {
				size_l,
				size_ll,
				size_h,
				size_hh,
				size_L,
				size_default
}				t_size_type;

typedef enum		e_type {
				type_u,
				type_d,
				type_i,
				type_x,
				type_X,
				type_o
}				t_type;

typedef struct		s_print_info
{
	int				flags;
	int				width;
	int				precision;
	t_size_type		size_type;
	t_type			type;
}					t_print_info;

int					putull_base(unsigned long long num, t_print_info *info);
int					putll_base(long long num, t_print_info *info);
int					ull_len_base(unsigned long long num, int base);
void				put_nsym(int count, int c);
void				ft_bzero(void *s, size_t n);
void				check_flag(t_print_info *info, const char **ptr);
int					ft_atoi(const char **str);
void				check_size(t_print_info *info, const char **ptr);
int					check_type(t_print_info *info, const char **ptr);
void				put_nsym(int count, int c);
int					parser(const char *format, va_list params, int ret_value);
int					ull_len_base_withflags(unsigned long long num,
											t_print_info *info);
int					ll_len_base_withflags(long long num,
											t_print_info *info);

#endif
