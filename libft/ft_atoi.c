/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:28:58 by anovoa            #+#    #+#             */
/*   Updated: 2024/02/11 13:31:17 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	const char	str[] = "  +3source";
	const char	str2[] = "         -304so6urce";
	const char	str3[] = " --34s4ource";
	const char	str4[] = " ++0304source";
	const char	str5[] = "9";
	const char	str6[] = "aa0304source";
	const char	str7[] = "0300source";

	printf("OG atoi: %i\n",atoi(str));
	printf("FT atoi: %i\n",ft_atoi(str));
	printf("OG atoi: %i\n",atoi(str2));
	printf("FT atoi: %i\n",ft_atoi(str2));
	printf("OG atoi: %i\n",atoi(str3));
	printf("FT atoi: %i\n",ft_atoi(str3));
	printf("OG atoi: %i\n",atoi(str4));
	printf("FT atoi: %i\n",ft_atoi(str4));
	printf("OG atoi: %i\n",atoi(str5));
	printf("FT atoi: %i\n",ft_atoi(str5));
	printf("OG atoi: %i\n",atoi(str6));
	printf("FT atoi: %i\n",ft_atoi(str6));
	printf("OG atoi: %i\n",atoi(str7));
	printf("FT atoi: %i\n",ft_atoi(str7));
	return (0);
}*/
