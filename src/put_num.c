/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 08:43:36 by nharra            #+#    #+#             */
/*   Updated: 2019/09/25 15:42:01 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"

int				putnum_base(unsigned long long num, unsigned base,
							t_print_info *info)
{
	unsigned long long	rank;
	char				*base_str;
	int					len_num;

	base_str = "0123456789abcdef";
	if (info->type == type_X)
		base_str = "0123456789ABCDEF";
	len_num = ull_len_base(num, base);
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

int				putull_base(unsigned long long num, t_print_info *info)
{
	int 				base;
	int					len = 0;

	if (info->type == type_X || info->type == type_x)
		base = 16;
	else if (info->type == type_o)
		base = 8;
	else
		base = 10;
	if ((info->flags & flag_hash) && num)
	{
		if (base == 16)
		{
			if (info->type == type_X)
				write(1, "0X", 2);
			else
				write(1, "0x", 2);
		}
		if (base == 8)
			write(1, "0", 1);
	}
	if ((len = ull_len_base_withflags(num, info)) < info->precision)
	{
		put_nsym(info->precision - len, '0');
		len = info->precision;
	}
	putnum_base(num, base, info);
	return (len);
}

int				putll_base(long long num, t_print_info *info)
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

void		put_nsym(int count, char c)
{
	int i;

	i = 0;
	while (i < count)
	{
		write(1, &c, 1);
		++i;
	}
}
