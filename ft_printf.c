/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 13:31:54 by nharra            #+#    #+#             */
/*   Updated: 2019/09/23 12:27:38 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int			ft_printf(const char *format, ...)
{
	va_list		params;
	int			ret_value;

	va_start(params, format);
	ret_value = parser(format, params, 0);
	va_end(params);
	return (ret_value);
}

void		put_nsym(int count, int c)
{
	int i;

	i = 0;
	while (i < count)
	{
		write(1, &c, 1);
		++i;
	}
}

int		main(void)
{
	ft_printf("fffff\n%d\naaa\n", -100);
}
