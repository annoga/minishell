/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:29:27 by anovoa            #+#    #+#             */
/*   Updated: 2024/03/03 17:48:25 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)str);
	while (str[i] && (len > i))
	{
		while ((str[i + j] == needle[j]) && (len > (i + j)))
			if (needle[++j] == '\0')
				return ((char *)(str + i));
		j = 0;
		i++;
	}
	return (NULL);
}
