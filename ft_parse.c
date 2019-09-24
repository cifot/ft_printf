/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:48:51 by nharra            #+#    #+#             */
/*   Updated: 2019/09/24 12:00:57 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include <unistd.h>

int					check_info(t_print_info *info, const char **ptr)
{
	ft_bzero(info, sizeof(*info));
	++(*ptr);
	check_flag(info, ptr);
	info->width = ft_atoi(ptr);
	if (**ptr == '.')
	{
		++(*ptr);
		info->precision = ft_atoi(ptr);
	}
	check_size(info, ptr);
	if (check_type(info, ptr) == -1)
		return (-1);
	return (0);
}

static int			print_d_continue(t_print_info *info, long long num)
{
	int len;

	len = 0;
	if (info->size_type == size_hh)
		num = (signed char)num;
	else if (info->size_type == size_h)
		num = (signed short int)num;
	len = ll_len_base_withflags(num, info);
	if (info->flags & flag_minus)
		putll_base(num, info);
	if (len < info->width)
	{
		if ((info->flags & flag_zero) && (info->precision == 0))
			put_nsym(info->width - len, '0');
		else
			put_nsym(info->width - len, ' ');
		len = info->width;
	}
	if (!(info->flags & flag_minus))
		putll_base(num, info);
	return (len);
}

static int			print_u_continue(t_print_info *info,
									unsigned long long num)
{
	int len;

	if (info->size_type == size_hh)
		num = (unsigned char)num;
	else if (info->size_type == size_h)
		num = (unsigned short int)num;
	len = ull_len_base_withflags(num, info);
	if (info->flags & flag_minus)
		len = putull_base(num, info);
	if (len < info->width)
	{
		if ((info->flags & flag_zero) && (info->precision == 0))
			put_nsym(info->width - len, '0');
		else
			put_nsym(info->width - len, ' ');
		len = info->width;
	}
	if (!(info->flags & flag_minus))
		putull_base(num, info);
	return (len);
}

int					print_params(t_print_info *info, va_list params)
{
	int						len;
	long long int			ll_num;
	unsigned long long int	ull_num;

	if (info->type == type_d || info->type == type_i)
	{
		if (info->size_type == size_ll)
			ll_num = va_arg(params, long long int);
		else if (info->size_type == size_l)
			ll_num = va_arg(params, long int);
		else
			ll_num = va_arg(params, int);
		return (print_d_continue(info, ll_num));
	}
	else
	{
		if (info->size_type == size_ll)
			ull_num = va_arg(params, unsigned long long int);
		else if (info->size_type == size_l)
			ull_num = va_arg(params, unsigned long int);
		else
			ull_num = va_arg(params, unsigned int);
		return (print_u_continue(info, ull_num));
	}
}

int					parser(const char *format, va_list params, int ret_value)
{
	const char		*ptr1;
	const char		*ptr2;
	int				tmp_value;
	t_print_info	info;

	ptr1 = format;
	ptr2 = format;
	tmp_value = 0;
	while (*ptr2)
	{
		if (*ptr2 == '%')
		{
			write(1, ptr1, ptr2 - ptr1);
			if ((check_info(&info, &ptr2) == -1) ||
			((tmp_value = print_params(&info, params)) == -1))
				return (-1);
			ret_value += tmp_value;
			tmp_value = 0;
			ptr1 = ptr2;
		}
		++tmp_value;
		++ptr2;
	}
	write(1, ptr1, ptr2 - ptr1);
	return (ret_value);
}
