/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 22:07:28 by nharra            #+#    #+#             */
/*   Updated: 2019/09/30 18:51:09 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int		print_p_continue(t_print_info *info, int len, char *ul_str)
{
	if (info->width > len)
	{
		if (info->flags & flag_minus)
			join_nsym(&ul_str, 1, info->width - len, ' ');
		else
			join_nsym(&ul_str, 0, info->width - len, ' ');
		len = info->width;
	}
	write(1, ul_str, len);
	free(ul_str);
	return (len);
}

int				print_p(t_print_info *info, va_list params)
{
	unsigned long	ul_num;
	int				len;
	char			*ul_str;

	ul_num = va_arg(params, unsigned long);
	if (ul_num == 0 && info->precision == 0)
	{
		ul_str = (char *)malloc(1);
		ul_str[0] = '\0';
	}
	else
		ul_str = num_base(ul_num, 16, info);
	len = ft_strlen(ul_str);
	if (info->precision > len)
	{
		join_nsym(&ul_str, 0, info->precision - len, '0');
		len = info->precision;
	}
	ft_join_beg(&ul_str, "0x");
	len += 2;
	return (print_p_continue(info, len, ul_str));
}
