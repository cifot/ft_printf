/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:58:39 by nharra            #+#    #+#             */
/*   Updated: 2019/09/26 11:16:52 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ull_len_base(unsigned long long num, int base)
{
	int count;

	count = 0;
	if (base < 2 || base > 16)
		return (0);
	if (num == 0)
		return (1);
	while (num)
	{
		num /= base;
		++count;
	}
	return (count);
}
