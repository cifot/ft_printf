/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:13:34 by nharra            #+#    #+#             */
/*   Updated: 2019/09/27 14:39:12 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					print_params(t_print_info *info, va_list params)
{
	if (info->type == type_d || info->type == type_i)
		return (print_d(info, params));
	else if (info->type == type_c)
		return (print_c(info, params));
	else if (info->type == type_p)
		return (print_p(info, params));
	else if (info->type == type_s)
		return (print_s(info, params));
	else if (info->type == type_x || info->type == type_X ||
			info->type == type_o)
		return (print_oxX(info, params));
	else if (info->type == type_u)
		return (print_u(info, params));
	else if (info->type == type_f)
		return (print_f(info, params));
	else if (info->type == type_percent)
		return (print_percent(info));
	else
		return (-1);
}
