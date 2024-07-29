/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:25:46 by angeln            #+#    #+#             */
/*   Updated: 2024/07/29 22:25:16 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_value(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != c && set[i] != '\0')
		i++;
	if (set[i] == c)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && check_value(s1[i], set))
		i++;
	while (check_value(s1[j], set) && j > i)
		j--;
	result = ft_substr(s1, i, (j - i + 1));
	return (result);
}
