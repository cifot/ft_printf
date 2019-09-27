/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:59:23 by nharra            #+#    #+#             */
/*   Updated: 2019/09/27 14:38:43 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>



static char		*makefract_str(unsigned long fract_num,
						t_print_info *info)
{
	char				*fract_str;
	int					i;
	unsigned long long	div;

	if (!(fract_str = (char *)malloc(info->precision + 2)))
		return (NULL);
	i = 1;
	div = (unsigned long)1 << 62;
	fract_str[0] = '.';
	while (i - 1 < info->precision)
	{
		fract_str[i] = '0' + (fract_num / div) % 10;
		fract_num *= 10;
		++i;
	}
	fract_str[i] = '\0';
	return (fract_str);
}

static char		*makeld_str(int power, unsigned long mantis, t_print_info *info)
{
	char				*int_part;
	char				*fract_part;

	fract_part = NULL;
	if (power >= 0 && power <= 64)
		int_part = num_base(mantis >> (64 - power), 10, info);
	else
		int_part = num_base(0, 10, info);
	if (info->precision == -1)
		info->precision = 6;
	if (info->precision > 0)
	{
		if (power >= 0 && power <= 64)
			fract_part = makefract_str((mantis << (power)) >> (power + 1), info);
		else
			fract_part = makefract_str(mantis, info);
	}
	ft_join(&int_part, fract_part);
	free(fract_part);
	return (int_part);
}

int				print_f(t_print_info *info, va_list params)
{
	long double				ld_num;
	unsigned int			power;
	unsigned long long int	mantis;
	void					*access;
	char					*ld_str;

	if (info->size_type == size_L)
		ld_num = va_arg(params, long double);
	else
		ld_num = va_arg(params, double);
	access = (void *)&ld_num;
	power = 16383 - ((*((unsigned int *)access) & 0x7fff) >> 16);
	mantis = ((unsigned long)((unsigned char *)access + 2));
	ld_str = makeld_str(power, mantis, info);
	mantis = write(1, ld_str, ft_strlen(ld_str));
	free(ld_str);
	return (mantis);
}
