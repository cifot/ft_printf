/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:58:39 by nharra            #+#    #+#             */
/*   Updated: 2019/09/25 13:54:35 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ull_len_base(unsigned long long num, int base)
{
	int count;

	count = 0;
	if (base < 2 || base > 16)
		return (0);
	if (num == 0)
		return (1);
	while (num)
	{
		num /= base;
		++count;
	}
	return (count);
}

int		ll_len_base_withflags(long long num, t_print_info *info)
{
	int len;
	unsigned long long	u_num;

	len = 0;
	u_num = num;
	if (info->precision == 0 && num == 0)
		return(0);
	if (info->flags & (flag_plus | flag_space))
		++len;
	if (num < 0)
	{
		if (len == 0)
			++len;
		u_num = -u_num;
	}
	return (len + ull_len_base(u_num, 10));
}

int		ull_len_base_withflags(unsigned long long num, t_print_info *info)
{
	int len;

	len = 0;
	if (info->flags & (flag_plus | flag_space))
		++len;
	else if ((info->flags & flag_hash) && num)
	{
		if ((info->type == type_X || info->type == type_x))
			len += 2;
		else if (info->type == type_o)
			++len;
	}
	if (info->type == type_o)
		return (len + ull_len_base(num, 8));
	else if (info->type == type_X || info->type == type_x)
		return (len + ull_len_base(num, 16));
	else
		return (len + ull_len_base(num, 10));
}
