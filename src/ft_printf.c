/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 13:31:54 by nharra            #+#    #+#             */
/*   Updated: 2019/09/26 22:06:36 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"
#include <stdio.h>

int			ft_printf(const char *format, ...)
{
	va_list		params;
	int			ret_value;

	va_start(params, format);
	ret_value = parser(format, params);
	va_end(params);
	return (ret_value);
}
