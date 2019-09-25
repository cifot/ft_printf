/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 22:07:28 by nharra            #+#    #+#             */
/*   Updated: 2019/09/24 22:31:58 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int		print_pointer(unsigned long ul_num)
{
	unsigned long long	rank;
	char				*base_str;
	int					len_num;

	base_str = "0123456789abcdef";
	rank = 1;
	len_num = 2;
	while (ul_num / rank >= 16)
		rank *= 16;
	write(1, "0x", 2);
	while (rank)
	{
		write(1, base_str + (ul_num / rank) % 16, 1);
		rank /= 16;
		++len_num;
	}
	return (len_num);
}

int			print_p(t_print_info *info, va_list params)
{
	unsigned long	ul_num;
	int				len;

	ul_num = va_arg(params, unsigned long);
	len = ull_len_base(ul_num, 16);
	if (info->width > len + 2)
	{
		if (info->flags & flag_minus)
		{
			print_pointer(ul_num);
			put_nsym(info->width - len - 2, ' ');
		}
		else
		{
			put_nsym(info->width - len - 2, ' ');
			print_pointer(ul_num);
		}
		return (info->width);
	}
	else
	{
		print_pointer(ul_num);
		return (len + 2);
	}
}
