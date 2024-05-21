/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_types_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 04:41:40 by anovoa            #+#    #+#             */
/*   Updated: 2023/12/20 18:27:00 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_left_blanks(t_params *p)
{
	int	i;

	i = 0;
	if (!p->neg && p->fill == 32 && p->max)
		while (i++ < p->max)
			if (!p_putchar(p->fill, p))
				return (0);
	return (1);
}

int	put_left_zeroes(t_params *p)
{
	int	i;

	i = 0;
	if (!p->neg && !p->bdot && p->fill == 48 && p->max)
		while (i++ < p->max)
			if (!p_putchar(p->fill, p))
				return (0);
	return (1);
}

int	put_right_blanks(t_params *p)
{
	int	i;

	i = 0;
	if (p->neg && p->max)
		while (i++ < p->max)
			if (!p_putchar(32, p))
				return (0);
	return (1);
}

int	solve_c(int c, t_params *p)
{
	int	size;

	size = 1;
	if (!set_padding(size, p) || !put_left_blanks(p))
		return (0);
	if (!p_putchar(c, p))
		return (0);
	if (!put_right_blanks(p))
		return (0);
	return (1);
}

int	solve_percent(t_params *p)
{
	int	size;

	size = 1;
	if (p->max)
		p->max = p->max - size;
	if (!put_left_blanks(p))
		return (0);
	if (!p_putchar('%', p))
		return (0);
	if (!put_right_blanks(p))
		return (0);
	return (1);
}
