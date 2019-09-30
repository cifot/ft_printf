/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:45:13 by nharra            #+#    #+#             */
/*   Updated: 2019/09/29 17:50:13 by nharra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "ft_printf.h"

int main(void)
{
	long double d;
	unsigned i = 0;
	unsigned char *p;
	unsigned long l;
	unsigned short int	sh;

	d = 299999.2;
	l = *((unsigned long *)&d);
	sh = *((unsigned short int*)(((unsigned long *)&d) + 1));
	printf("%Lf\n", d);
	ft_printf("myft = %Lf\n", d);
	printf("%lu\n", l);
	printf("%hu\n", sh);
	p = (unsigned char *)&d;
	while (i < sizeof(d))
	{
		int j = 0;
		while (j < 8)
		{
			printf("%d", (*p & (1 << (7 - j)) ? 1 : 0));
			++j;
		}
		printf(" ");
		++p;
		++i;
	}
	printf("\n");
	p = (unsigned char *)&l;
	i = 0;
	while (i < sizeof(l))
	{
		int j = 0;
		while (j < 8)
		{
			printf("%d", (*p & (1 << (7 - j)) ? 1 : 0));
			++j;
		}
		printf(" ");
		++p;
		++i;
	}
	printf("\n");
}
