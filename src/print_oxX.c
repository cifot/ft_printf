/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oxx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:57:30 by nharra            #+#    #+#             */
/*   Updated: 2019/09/30 19:10:50 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static void		check_flags(t_print_info *info, char **s,
							unsigned long long num)
{
	if (info->type == type_x)
	{
		if (num != 0)
			ft_join_beg(s, "0x");
	}
	else if (info->type == type_X)
	{
		if (num != 0)
			ft_join_beg(s, "0X");
	}
	else if (info->type == type_o)
		if (num != 0 && **s != '0')
			ft_join_beg(s, "0");
}

static void		with_hash(t_print_info *info, char **s, int *len,
							unsigned long long num)
{
	int i;

	if (num == 0)
		i = 0;
	else
		i = (info->type == type_o) ? 1 : 2;
	if (info->flags & flag_minus)
	{
		check_flags(info, s, num);
		join_nsym(s, 1, info->width - *len - i, ' ');
	}
	else
	{
		if ((info->flags & flag_zero) && info->precision == -1)
		{
			join_nsym(s, 0, info->width - *len - i, '0');
			check_flags(info, s, num);
		}
		else
		{
			check_flags(info, s, num);
			join_nsym(s, 0, info->width - *len - i, ' ');
		}
	}
}

static void		without_hash(t_print_info *info, char **s, int *len)
{
	if (info->width > *len)
	{
		if (info->flags & flag_minus)
		{
			join_nsym(s, 1, info->width - *len, ' ');
		}
		else
		{
			if (info->flags & flag_zero)
				join_nsym(s, 0, info->width - *len, '0');
			else
				join_nsym(s, 0, info->width - *len, ' ');
		}
	}
}

static int		print_oxx_continue(t_print_info *info,
									unsigned long long num)
{
	char	*s;
	int		len;

	if (!(s = ull_base(num, info)))
		return (0);
	len = ft_strlen(s);
	if (info->precision > len)
	{
		join_nsym(&s, 0, info->precision - len, '0');
		len = info->precision;
	}
	if (info->precision >= 0)
		info->flags = info->flags & (~flag_zero);
	if (info->flags & flag_hash)
		with_hash(info, &s, &len, num);
	else
		without_hash(info, &s, &len);
	len = write(1, s, ft_strlen(s));
	free(s);
	return (len);
}

int				print_oxx(t_print_info *info, va_list params)
{
	unsigned long long	ull_num;

	if (info->size_type == size_ll)
		ull_num = va_arg(params, unsigned long long int);
	else if (info->size_type == size_l)
		ull_num = va_arg(params, unsigned long int);
	else
		ull_num = va_arg(params, unsigned int);
	if (info->size_type == size_hh)
		ull_num = (unsigned char)ull_num;
	else if (info->size_type == size_h)
		ull_num = (unsigned short int)ull_num;
	if (info->precision == 0 && ull_num == 0)
		return (print_oxx_zero_prec(info));
	return (print_oxx_continue(info, ull_num));
}
