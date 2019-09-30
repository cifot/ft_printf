/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:14:19 by nharra            #+#    #+#             */
/*   Updated: 2019/09/30 19:14:04 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static void		check_flags(t_print_info *info, char **s, int flag)
{
	if (flag == 0)
	{
		if (info->flags & flag_plus)
			ft_join_beg(s, "+");
		else if (info->flags & flag_space)
			ft_join_beg(s, " ");
		return ;
	}
	flag = 0;
	if (info->flags & flag_plus)
		flag = 1;
	if ((info->flags & flag_plus) && (info->flags & flag_minus))
		write(1, "+", flag = 1);
	if ((info->flags & flag_space) && (info->flags & flag_minus))
		write(1, " ", flag = 1);
	put_nsym(info->width - flag, ' ');
	if (((info->flags & flag_plus) && !(info->flags & flag_minus)))
		write(1, "+", 1);
}

static void		without_minus(t_print_info *info, char **s, int *len)
{
	int i;

	i = ((info->flags & flag_plus) || ((info->flags & flag_space))) ? 1 : 0;
	if (info->flags & flag_minus)
	{
		check_flags(info, s, 0);
		join_nsym(s, 1, info->width - *len - i, ' ');
	}
	else
	{
		if ((info->flags & flag_zero) && info->precision == -1)
		{
			join_nsym(s, 0, info->width - *len - i, '0');
			check_flags(info, s, 0);
		}
		else
		{
			check_flags(info, s, 0);
			join_nsym(s, 0, info->width - *len - i, ' ');
		}
	}
	*len = info->width;
}

static void		with_minus(t_print_info *info, char **s, int *len)
{
	if (info->width > *len)
		if (info->flags & flag_minus)
		{
			join_nsym(s, 1, info->width - *len - 1, ' ');
			ft_join_beg(s, "-");
		}
		else
		{
			if (info->flags & flag_zero)
			{
				if (info->flags & flag_zero)
					join_nsym(s, 0, info->width - *len - 1, '0');
				ft_join_beg(s, "-");
				if (!(info->flags & flag_zero))
					join_nsym(s, 0, info->width - *len - 1, ' ');
			}
			else
			{
				ft_join_beg(s, "-");
				join_nsym(s, 0, info->width - *len - 1, ' ');
			}
		}
	else
		ft_join_beg(s, "-");
}

static int		print_d_continue(t_print_info *info, long long num)
{
	char	*s;
	int		len;

	if (!(s = ll_base(num, info)))
		return (0);
	len = ft_strlen(s);
	if (info->precision > len)
	{
		join_nsym(&s, 0, info->precision - len, '0');
		len = info->precision;
	}
	if (info->precision >= 0)
		info->flags = info->flags & (~flag_zero);
	if (num < 0)
		with_minus(info, &s, &len);
	else
		without_minus(info, &s, &len);
	len = write(1, s, ft_strlen(s));
	free(s);
	return (len);
}

int				print_d(t_print_info *info, va_list params)
{
	unsigned long long	ll_num;

	if (info->size_type == size_ll)
		ll_num = va_arg(params, long long int);
	else if (info->size_type == size_l)
		ll_num = va_arg(params, long int);
	else
		ll_num = va_arg(params, int);
	if (info->size_type == size_hh)
		ll_num = (char)ll_num;
	else if (info->size_type == size_h)
		ll_num = (short int)ll_num;
	if (info->precision == 0 && ll_num == 0)
	{
		check_flags(info, NULL, 1);
		return (info->width);
	}
	return (print_d_continue(info, ll_num));
}
