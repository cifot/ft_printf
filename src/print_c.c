/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:42:28 by nharra            #+#    #+#             */
/*   Updated: 2019/09/25 13:04:45 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int		print_c(t_print_info *info, va_list params)
{
	char c;

	c = va_arg(params, int);
	if (info->width <= 1)
		write(1, &c, 1);
	else
	{
		if (info->flags & flag_minus)
		{
			write(1, &c, 1);
			put_nsym(info->width - 1, ' ');
		}
		else
		{
			put_nsym(info->width - 1, ' ');
			write(1, &c, 1);
		}
	}
	return (info->width <= 1 ? 1 : info->width);
}
