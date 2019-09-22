/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 08:43:36 by nharra            #+#    #+#             */
/*   Updated: 2019/09/22 19:23:10 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"

int		putull_base(unsigned long long num, int base, t_print_info *info)
{
	unsigned long long	rank;
	char				*base_str;
	int					len_num;

	base_str = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (-1);
	if (base == 16 && info->flags == type_X)
		base_str = "0123456789ABCDEF";
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

int		putll_base(long long num, int base,t_print_info *info)
{
	unsigned long long	u_num;
	int					len;

	len = 0;
	if (base < 2 || base > 16)
	{
		return (-1);
	}
	u_num = num;
	if (num < 0)
	{
		++len;
		write(1, "-", 1);
		u_num = -u_num;
	}
	return (len + putull_base(u_num, base, info));
}
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

void	put_nsym(int count, int c)
{
	int i;

	i = 0;
	while (i < count)
	{
		write(1, &c, 1);
		++i;
	}
}
