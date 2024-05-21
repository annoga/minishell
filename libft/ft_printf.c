/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:12:58 by anovoa            #+#    #+#             */
/*   Updated: 2024/02/11 17:54:30 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reset_params(t_params *p)
{
	p->reset = 0;
	p->max = 0;
	p->dot = 0;
	p->bdot = 0;
	p->neg = 0;
	p->prefx = 0;
	p->sign = ' ';
	p->zero = 0;
	p->fill = ' ';
	p->type = ' ';
}

static int	get_precision(const char *s, t_params *p)
{
	int	offset;

	offset = 0;
	while (s[offset] && s[offset] == '0')
		offset++;
	if (ft_isdigit(s[offset]))
		p->dot = ft_atoi(s + offset);
	if (p->dot)
		offset = offset + count_digits_base(p->dot, 10);
	return (offset);
}

static int	solve_modifiers(const char **s, t_params *p)
{
	if (**s == '-')
		p->neg = 1;
	else if (**s == '+')
	{
		p->sign = '+';
		p->prefx = 1;
	}
	else if (**s > '0' && **s <= '9')
	{
		p->max = ft_atoi(*s);
		*s += count_digits_base(p->max, 10) - 1;
	}
	else if (**s == '.')
	{
		p->bdot = 1;
		p->dot = 0;
		*s = *s + get_precision(*s + 1, p);
	}
	else if (**s == ' ' || **s == '#')
		p->prefx = 1;
	else if (**s == '0')
		p->fill = '0';
	else
		return (0);
	return (1);
}

static int	solve_type(va_list *args, t_params *p)
{
	p->reset = 1;
	if (p->type == 'd' || p->type == 'i')
		return (solve_nbr(va_arg(*args, int), p));
	if (p->type == 'u')
		return (solve_nbr(va_arg(*args, unsigned int), p));
	if (p->type == 'x' || p->type == 'X')
		return (solve_hex(va_arg(*args, unsigned int), "0x", p));
	if (p->type == 'p')
		return (solve_ptr(va_arg(*args, unsigned long), p));
	if (p->type == 's')
		return (solve_str(va_arg(*args, char *), p));
	if (p->type == 'c')
		return (solve_c(va_arg(*args, int), p));
	if (p->type == '%')
		return (solve_percent(p));
	else
		return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list		arg_ptr;
	t_params	p;

	p.wc = 0;
	reset_params(&p);
	va_start(arg_ptr, s);
	while (*s)
	{
		if (*s == '%')
		{
			while (++s && *s != '%' && !ft_isalpha(*s))
				p.reset = solve_modifiers(&s, &p);
			p.type = *s;
			if (!solve_type(&arg_ptr, &p))
				return (-1);
		}
		else
			if (!p_putchar(*s, &p))
				return (-1);
		s++;
		if (p.reset)
			reset_params(&p);
	}
	va_end(arg_ptr);
	return (p.wc);
}
