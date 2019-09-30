/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oxx_zero_prec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:32:49 by nharra            #+#    #+#             */
/*   Updated: 2019/09/30 16:36:48 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int		print_oxx_zero_prec(t_print_info *info)
{
	int		len;

	len = 0;
	put_nsym(info->width - 1, ' ');
	if (info->type == type_o && info->flags == flag_hash)
	{
		write(1, "0", 1);
		return (info->width > 0 ? info->width : 1);
	}
	else if (info->width > 0)
		write(1, " ", 1);
	return (info->width > 0 ? info->width : 0);
}
