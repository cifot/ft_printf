/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:59:23 by nharra            #+#    #+#             */
/*   Updated: 2019/09/29 17:50:01 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>


static char		*makefract_str(unsigned long fract_num,
						t_print_info *info, int power)
{
	char				*fract_str;
	int					i;
	unsigned long long	div;

	if (!(fract_str = (char *)malloc(info->precision + 2)))
		return (NULL);
	div = 1;
	i = 0;
	while (i++ < power)
		div *= 2;
	i = 1;
	fract_str[0] = '.';
	while (i - 1 < info->precision)
	{
		fract_str[i] = '0' + (fract_num / div)% 10;
		fract_num = fract_num % div;
		div /= 10;
		++i;
	}
	fract_str[i] = '\0';
	return (fract_str);
}

static char		*makeld_str(int power, unsigned long mantis, t_print_info *info)
{
	char				*int_part;
	char				*fract_part;

	printf("\npower = %d\n mant = %lu\n", power, (mantis << (power + 1)) >> (power + 1));
	fract_part = NULL;
	if (power >= 0 && power <= 63)
		int_part = num_base(mantis >> (63 - power), 10, info);
	else
		int_part = num_base(0, 10, info);
	if (info->precision == -1)
		info->precision = 6;
	if (info->precision > 0)
	{
		if (power >= 0 && power <= 63)
			fract_part = makefract_str((mantis << (power + 1)), info, power);
		else
			fract_part = makefract_str(mantis, info, -1);
	}
	ft_join(&int_part, fract_part);
	free(fract_part);
	return (int_part);
}

int				print_f(t_print_info *info, va_list params)
{
	long double				ld_num;
	int						power;
	unsigned long			mantis;
	char					*ld_str;

	if (info->size_type == size_L)
		ld_num = va_arg(params, long double);
	else
		ld_num = va_arg(params, double);
	power = *((unsigned short int*)(((unsigned long *)&ld_num) + 1)) - 16383;
	mantis = *((unsigned long *)&ld_num);
	ld_str = makeld_str(power, mantis, info);
	mantis = write(1, ld_str, ft_strlen(ld_str));
	free(ld_str);
	return (mantis);
}
