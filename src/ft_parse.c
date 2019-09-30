/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:48:51 by nharra            #+#    #+#             */
/*   Updated: 2019/09/30 18:58:49 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include <unistd.h>

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

int					parser(const char *format, va_list params)
{
	const char		*ptr1;
	const char		*ptr2;
	int				ret_value;
	t_print_info	info;

	ret_value = 0;
	ptr1 = format;
	ptr2 = format;
	while (*ptr2)
	{
		if (*ptr2 == '%')
		{
			ret_value += write(1, ptr1, ptr2 - ptr1);
			if (check_info(&info, &ptr2) != -1)
				ret_value += print_params(&info, params);
			ptr1 = ptr2;
		}
		else
			++ptr2;
	}
	ret_value += write(1, ptr1, ptr2 - ptr1);
	return (ret_value);
}
