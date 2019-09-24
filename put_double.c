/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:35:44 by nharra            #+#    #+#             */
/*   Updated: 2019/09/24 14:08:51 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		make_mantis(double d_num, long *mantis)
{
	long *ptr;

	ptr = (long *)&d_num;
	*mantis = *ptr & 0xfffffffffffff;
}

static void		make_shift(double d_num, int *shift)
{
	long *ptr;

	ptr = (long *)&d_num;
	*shift = ((*ptr & 0x7ff0000000000000) >> 52) - 1023;
}

int				put_double(double d_num)
{
	int			len;
	int			shift;
	long long	mantis;

	make_mantis(d_num, &mantis);
	make_shift(d_num, &shift);
}
