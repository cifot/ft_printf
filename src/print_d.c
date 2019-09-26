/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:14:19 by nharra            #+#    #+#             */
/*   Updated: 2019/09/26 11:16:17 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_d_continue(t_print_info *info, long long num)
{
	char	*s;
	size_t	len;

	len = ll_len_base(num, info);
	if (info->flags & flag_minus)
	{
		len = putll_base(num, info);
		if (info->width > len)
		{
			put_nsym(info->width - len, ' ');
			len = info->width;
		}
	}
	else if (len < info->width)
	{
		if ((info->flags & flag_zero))
			put_nsym(info->width - len, '0');
		else
			put_nsym(info->width - len, ' ');
		len = info->width;
		putll_base(num, info);
	}
	else
		len = putll_base(num, info);
	return (len);
}

int			print_d(t_print_info *info, va_list params)
{
	long long	ll_num;

	if (info->size_type == size_ll)
		ll_num = va_arg(params, long long int);
	else if (info->size_type == size_l)
		ll_num = va_arg(params, long int);
	else
		ll_num = va_arg(params, int);
	if (info->size_type == size_hh)
		ll_num = (signed char)ll_num;
	else if (info->size_type == size_h)
		ll_num = (signed short int)ll_num;
	if (info->precision == 0 && ll_num == 0)
		return (0);
	return (print_d_continue(info, ll_num));
}
