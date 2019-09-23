/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 08:43:36 by nharra            #+#    #+#             */
/*   Updated: 2019/09/23 12:16:03 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"

int		putnum_base(unsigned long long num, int base, t_print_info *info)
{
	unsigned long long	rank;
	char				*base_str;
	int					len_num;

	base_str = "0123456789abcdef";
	if (info->type == type_X)
	{
		base_str = "0123456789ABCDEF";
	}
	len_num = ull_len_base(num, base);
	if (info->precision > len_num)
	{
		put_nsym(info->precision - len_num,'0');
		len_num = info->precision;
	}
	rank = 1;
	while (num / rank >= base)
		rank *= base;
	while (rank)
	{
		write(1, base_str + (num / rank) % base, 1);
		rank /= base;
	}
	return (len_num);
}

int		putull_base(unsigned long long num, t_print_info *info)
{
	int 				base;
	int					len;

	if (info->type == type_X || info->type == type_x)
	{
		base = 16;
		if (info->flags & flag_hash)
		{
			len = 2;
			write(1, "0x", 1);
		}
	}
	else if (info->type == type_o)
	{
		base = 8;
		if (info->flags & flag_hash)
		{
			len = 1;
			write(1, "0", 1);
		}
	}
	else
		base = 8;
	return (len + putnum_base(num, base, info));
}

int		putll_base(long long num, t_print_info *info)
{
	unsigned long long	u_num;
	int					len;

	len = 0;
	u_num = num;
	if (num >= 0)
	{
		if (info->flags & flag_plus)
		{
			++len;
			write(1, "+", 1);
		}
		else if (info->flags & flag_space)
		{
			++len;
			write(1, " ", 1);
		}
	}
	else
	{
		++len;
		write(1, "-", 1);
		u_num = -u_num;
	}
	return (len + putnum_base(u_num, 10, info));
}
