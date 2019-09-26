/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:49:48 by nharra            #+#    #+#             */
/*   Updated: 2019/09/26 21:48:47 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int				print_s_continue(t_print_info *info, const char *s)
{
	int		len;

	len = ft_strlen(s);
	if ((info->precision > 0) && (len > info->precision))
		len = info->precision;
	if (info->width > len)
	{
		if (info->flags & flag_minus)
			write(1, s, len);
		put_nsym(info->width - len, ' ');
		if (!(info->flags & flag_minus))
			write(1, s, len);
	}
	else
		write(1, s, len);
	return (len > info->width ? len : info->width);
}

int				print_s(t_print_info *info, va_list params)
{
	char	*s;

	s = va_arg(params, char*);
	if (s == NULL)
		return (print_s_continue(info, "(null)"));
	else
		return (print_s_continue(info, s));
}
