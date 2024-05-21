/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 04:42:25 by anovoa            #+#    #+#             */
/*   Updated: 2024/03/09 07:38:16 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	p_putchar(char c, t_params *p)
{
	if (write(2, &c, 1) == -1)
		return (0);
	p->wc = p->wc + 1;
	return (1);
}

int	p_putstr(char *s, t_params *p)
{
	if (!s && !p_putstr("(null)", p))
		return (0);
	if (s)
	{
		while (*s)
		{
			if (!p_putchar(*s, p))
				return (0);
			s++;
		}
	}
	return (1);
}

int	p_putnbr(unsigned int n, t_params *p)
{
	if (n > 9)
	{
		if (!p_putnbr(n / 10, p) || !p_putchar(n % 10 + '0', p))
			return (0);
	}
	else if (n <= 9)
		if (!p_putchar(n + '0', p))
			return (0);
	return (1);
}

int	p_puthex(unsigned int n, char *base, t_params *p)
{
	if (n > 15)
	{
		if (!p_puthex(n / 16, base, p) || !p_putchar(base[n % 16], p))
			return (0);
	}
	else if (n <= 15)
		if (!p_putchar(base[n], p))
			return (0);
	return (1);
}

int	p_putptr(unsigned long n, t_params *p)
{
	char	*base;

	base = "0123456789abcdef";
	if (n > 15)
	{
		if (!p_putptr(n / 16, p) || !p_putchar(base[n % 16], p))
			return (0);
	}
	else if (n <= 15)
		if (!p_putchar(base[n], p))
			return (0);
	return (1);
}
