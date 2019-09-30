/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:59:23 by nharra            #+#    #+#             */
/*   Updated: 2019/09/30 17:34:22 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static char		*makefract_str(long double fract_num,
									t_print_info *info)
{
	char				*fract_str;
	int					i;
	double				div;

	if (!(fract_str = (char *)malloc(info->precision + 2)))
		return (NULL);
	div = 0x8000000000000000UL;
	i = 1;
	fract_str[0] = '.';
	fract_num *= 10;
	while (i - 1 < info->precision)
	{
		fract_str[i] = '0' + (unsigned long)(fract_num / div) % 10;
		fract_num = fract_num * 10;
		++i;
	}
	if ((unsigned long)(fract_num / div) % 10 > 4)
		++fract_str[i - 1];
	fract_str[i] = '\0';
	return (fract_str);
}

static char		*makeld_str(t_print_info *info,
							long double ld_num)
{
	char				*int_part;
	char				*fract_part;
	unsigned long		mantis;
	int					power;

	fract_part = NULL;
	int_part = num_base((unsigned long long)ld_num, 10, info);
	if (info->precision == -1)
		info->precision = 6;
	ld_num = ld_num - (unsigned long)ld_num;
	mantis = *((unsigned long *)&ld_num);
	power = *((unsigned short int*)(((unsigned long *)&ld_num) + 1)) - 16383;
	if (info->precision > 0)
		fract_part = makefract_str(mantis >> (-power), info);
	else if (ld_num >= 0.5)
		int_part[ft_strlen(int_part) - 1]++;
	else if (info->flags & flag_hash)
		ft_join(&int_part, ".");
	ft_join(&int_part, fract_part);
	free(fract_part);
	return (int_part);
}

static void		check(char **ld_str, t_print_info *info, int flag)
{
	int		len;

	if (info->flags & flag_space)
		if (flag == 0)
			ft_join_beg(ld_str, " ");
	len = ft_strlen(*ld_str);
	if (info->flags & flag_minus)
		join_nsym(ld_str, 1, info->width - len, ' ');
	else
		join_nsym(ld_str, 0, info->width - len, ' ');
}

static void		round(char **ld_str, char *ptr)
{
	ptr = *ld_str;
	while (*ptr)
		++ptr;
	--ptr;
	while (*ptr == '0' + 10)
	{
		*(ptr--) = '0';
		*ptr += 1;
	}
	if (*ptr == '.' + 1)
	{
		*(ptr--) = '.';
		*ptr += 1;
		while ((*ptr == '0' + 10) && ptr != *ld_str)
		{
			*(ptr--) = '0';
			*ptr += 1;
		}
	}
	if (ptr == *ld_str && *ptr == '0' + 10)
	{
		*ptr = '0';
		ft_join_beg(ld_str, "1");
	}
}

int				print_f(t_print_info *info, va_list params)
{
	long double				ld_num;
	char					*ld_str;
	int						flag;

	if (info->size_type == size_L)
		ld_num = va_arg(params, long double);
	else
		ld_num = va_arg(params, double);
	flag = (ld_num < 0 ? 1 : 0);
	ld_num = (ld_num >= 0 ? ld_num : -ld_num);
	ld_str = makeld_str(info, ld_num);
	if (info->precision > 0)
		round(&ld_str, NULL);
	if (flag)
		ft_join_beg(&ld_str, "-");
	check(&ld_str, info, flag);
	flag = write(1, ld_str, ft_strlen(ld_str));
	free(ld_str);
	return (flag);
}
