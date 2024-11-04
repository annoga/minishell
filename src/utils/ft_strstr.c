/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:17:12 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:17:13 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strstr(const char *str, const char *needle)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == needle[j])
		{
			if (needle[j] == '\0')
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
