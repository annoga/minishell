/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:55:17 by anovoa            #+#    #+#             */
/*   Updated: 2024/02/21 20:06:14 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit_at_base(char c, int base)
{
	int	max_digit;

	if (base <= 10)
		max_digit = '0' + base;
	else
		max_digit = 'a' + base - 10;
	if (c >= '0' && c <= '9' && c < max_digit)
		return (c - '0');
	if (c >= 'a' && c <= 'f' && c < max_digit)
		return (c - 'a' + 10);
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	digit;
	int	result;

	sign = 1;
	result = 0;
	if (!str)
		return (0);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	digit = get_digit_at_base(ft_tolower(*str), str_base);
	while (digit != -1)
	{
		result = result * str_base + digit;
		str++;
		digit = get_digit_at_base(ft_tolower(*str), str_base);
	}
	return (sign * result);
}

unsigned int	ft_atoui_base(const char *str, int str_base)
{
	int				digit;
	unsigned int	result;

	result = 0;
	if (!str)
		return (0);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	digit = get_digit_at_base(ft_tolower(*str), str_base);
	while (digit != -1)
	{
		result = result * str_base + (unsigned int)digit;
		str++;
		digit = get_digit_at_base(ft_tolower(*str), str_base);
	}
	return (result);
}
