/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 02:52:20 by anovoa            #+#    #+#             */
/*   Updated: 2023/07/20 12:59:58 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countlength(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count += 1;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*dest;
	size_t			len;

	len = ft_countlength(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	num = 0;
	dest[0] = '-';
	dest[len] = '\0';
	if (n < 0)
		num = -n;
	else if (n == 0)
		dest[0] = '0';
	else
		num = n;
	while (num > 0)
	{
		dest[len - 1] = num % 10 + '0';
		num /= 10;
		len--;
	}
	return (dest);
}
