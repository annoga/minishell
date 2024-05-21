/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 04:42:07 by anovoa            #+#    #+#             */
/*   Updated: 2024/02/11 17:56:26 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits_base(unsigned long n, int base)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		n /= base;
		count += 1;
	}
	return (count);
}

int	set_padding(int size, t_params *p)
{
	if (p->type != 's' && p->type != 'c' && p->type != '%')
	{
		if (p->zero && p->bdot && p->dot == 0)
			size = 0;
		if (p->bdot)
			p->fill = 32;
		if (size != 0 && size >= p->dot)
		{
			p->dot = 0;
			p->bdot = 0;
		}
	}
	else if (p->type == 's')
		if (p->dot >= size)
			p->dot = 0;
	if (p->dot - size > 0)
		p->dot = p->dot - size;
	else
		p->dot = 0;
	if (p->max - p->prefx - p->dot - size > 0)
		p->max = p->max - p->prefx - p->dot - size;
	else
		p->max = 0;
	return (1);
}

int	put_precision(t_params *p)
{
	int	i;

	i = 0;
	while (i++ < p->dot)
		if (!p_putchar('0', p))
			return (0);
	return (1);
}
