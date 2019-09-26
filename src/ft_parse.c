/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:48:51 by nharra            #+#    #+#             */
/*   Updated: 2019/09/25 14:09:52 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>

int					check_info(t_print_info *info, const char **ptr)
{
	ft_bzero(info, sizeof(*info));
	++(*ptr);
	check_flag(info, ptr);
	info->width = ft_atoi(ptr);
	if (**ptr == '.')
	{
		++(*ptr);
		info->precision = ft_atoi(ptr);
		if (*(*ptr - 1) != '.' && (*(*ptr - 1) > '9' || *(*ptr - 1) < '0'))
			info->precision = -1;
	}
	else
		info->precision = -1;
	check_size(info, ptr);
	if (check_type(info, ptr) == -1)
		return (-1);
	return (0);
}

int					parser(const char *format, va_list params, int ret_value)
{
	const char		*ptr1;
	const char		*ptr2;
	int				tmp_value;
	t_print_info	info;

	ptr1 = format;
	ptr2 = format;
	tmp_value = 0;
	while (*ptr2)
	{
		if (*ptr2 == '%')
		{
			write(1, ptr1, ptr2 - ptr1);
			ret_value += tmp_value;
			if ((check_info(&info, &ptr2) == -1) ||
			((tmp_value = print_params(&info, params)) == -1))
				return (-1);
			ret_value += tmp_value;
			tmp_value = 0;
			ptr1 = ptr2;
		}
		else
		{
			++tmp_value;
			++ptr2;
		}
	}
	write(1, ptr1, ptr2 - ptr1);
	return (ret_value + ptr2 - ptr1);
}