/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:19:16 by nharra            #+#    #+#             */
/*   Updated: 2019/09/26 11:45:49 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	print_u_continue(t_print_info *info,
									unsigned long long num)
{
	char	*s;
	size_t	len;

	if (!(s = ull_base(num, info)))
		return (0);
	if (info->flags & flag_minus)
	{
		if (info->precision > 0)
		{

		}
	}
	else if (len < info->width)
	{
		if ((info->flags & flag_zero))
			put_nsym(info->width - len, '0');
		else
			put_nsym(info->width - len, ' ');
		len = info->width;
		putull_base(num, info);
	}
	else
		len = putull_base(num, info);
	return (len);
}

int			print_u(t_print_info *info, va_list params)
{
	unsigned long long	ull_num;

	if (info->size_type == size_ll)
		ull_num = va_arg(params, unsigned long long int);
	else if (info->size_type == size_l)
		ull_num = va_arg(params, unsigned long int);
	else
		ull_num = va_arg(params, unsigned int);
	if (info->size_type == size_hh)
		ull_num = (unsigned char)ull_num;
	else if (info->size_type == size_h)
		ull_num = (unsigned short int)ull_num;
	if (info->precision == 0 && ull_num == 0)
		return (0);
	return (print_u_continue(info, ull_num));
}
