/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_percent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:50:51 by nharra            #+#    #+#             */
/*   Updated: 2019/09/25 12:37:00 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int			print_percent(t_print_info *info)
{
	if (info->width <= 1)
		write(1, "%", 1);
	else
	{
		if (info->flags & flag_minus)
		{
			write(1, "%", 1);
			put_nsym(info->width - 1, ' ');
		}
		else
		{
			if (info->flags & flag_zero)
				put_nsym(info->width - 1, '0');
			else
				put_nsym(info->width - 1, ' ');
			write(1, "%", 1);
		}
	}
	return (info->width <= 1 ? 1 : info->width);
}
