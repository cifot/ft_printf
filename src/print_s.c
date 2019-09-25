/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:49:48 by nharra            #+#    #+#             */
/*   Updated: 2019/09/24 22:33:02 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int				print_s(t_print_info *info, va_list params)
{
	char	*s;
	int		len;

	s = va_arg(params, char*);
	len = ft_strlen(s);
	if ((info->precision > 0) && (len > info->precision))
		len = info->precision;
	if (info->width > len)
	{
		if (info->flags & flag_minus)
		{
			write(1, s, len);
			put_nsym(info->width - len, ' ');
		}
		else
		{
			put_nsym(info->width - len, ' ');
			write(1, s, len);
		}
	}
	else
		write(1, s, len);
	return (len > info->width ? len : info->width);
}
