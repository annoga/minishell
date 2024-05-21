/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_types_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 04:48:17 by anovoa            #+#    #+#             */
/*   Updated: 2024/02/11 17:56:13 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	del_ptr(char **ptr, t_params *p)
{
	if (p->bdot)
	{
		free(*ptr);
		ptr = NULL;
	}
	return (0);
}

int	solve_ptr(unsigned long ptr, t_params *p)
{
	int	size;

	p->prefx = 2;
	size = count_digits_base(ptr, 16);
	if (set_padding(size, p) && !put_left_blanks(p))
		return (0);
	if (!p_putstr("0x", p))
		return (0);
	if (!put_left_zeroes(p))
		return (0);
	if (!p_putptr(ptr, p))
		return (0);
	return (put_right_blanks(p));
}

int	solve_str(char *s, t_params *p)
{
	p->prefx = 0;
	if (!s)
		s = "(null)";
	if (p->bdot && !p->max && *s == '\0')
		return (p_putstr(s, p));
	if (p->bdot)
	{
		s = ft_substr(s, 0, p->dot);
		if (!s)
			return (0);
	}
	if (set_padding(ft_strlen(s), p) && !put_left_blanks(p))
		return (del_ptr(&s, p));
	if (!put_left_zeroes(p))
		return (del_ptr(&s, p));
	if (!p_putstr(s, p) || del_ptr(&s, p))
		return (del_ptr(&s, p));
	return (put_right_blanks(p));
}

int	solve_nbr(long n, t_params *p)
{
	if (!n)
		p->zero = 1;
	else if (n < 0)
	{
		n = -n;
		p->prefx = 1;
		p->sign = '-';
	}
	if (p->prefx && p->sign == 32)
		if (!p_putchar(p->sign, p))
			return (0);
	if (!set_padding(count_digits_base(n, 10), p) || !put_left_blanks(p))
		return (0);
	if (p->sign != 32)
		if (!p_putchar(p->sign, p))
			return (0);
	if (!put_left_zeroes(p))
		return (0);
	if (!put_precision(p))
		return (0);
	if (n == 0 && p->bdot && !p->dot)
		;
	else if (!p_putnbr((unsigned int)n, p))
		return (0);
	return (put_right_blanks(p));
}

int	solve_hex(unsigned int n, char *prefix, t_params *p)
{
	char	*base;

	if (!n)
		p->zero = 1;
	base = "0123456789abcdef";
	if (p->type == 'X')
	{
		prefix = "0X";
		base = "0123456789ABCDEF";
	}
	if (p->prefx)
		(1 && (n && (p->prefx = 2)) || (p->prefx = 0));
	if (set_padding(count_digits_base(n, 16), p) && !put_left_blanks(p))
		return (0);
	if (p->prefx && n && !p_putstr(prefix, p))
		return (0);
	if (!put_left_zeroes(p))
		return (0);
	if (!put_precision(p))
		return (0);
	if (n == 0 && p->bdot && !p->dot)
		;
	else if (!p_puthex(n, base, p))
		return (0);
	return (put_right_blanks(p));
}
