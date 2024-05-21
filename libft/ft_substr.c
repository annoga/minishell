/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:09:35 by angeln            #+#    #+#             */
/*   Updated: 2023/07/18 05:01:36 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*result;
	size_t			size;

	i = 0;
	j = 0;
	size = ft_strlen(s);
	while ((start < size) && s[start + i] && i < len)
		i++;
	result = (char *)malloc(i + 1);
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = s[start + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}
/*#include <stdio.h>
int	main(void)
{
	char const	*src = "Soy una frase demasiado larga";
	char	*result;

	result = ft_substr(src,25,10);
	printf("String: \"%s\"\n",src);
	printf("Substring: \"%s\"\n",result);
	return (0);
}*/
