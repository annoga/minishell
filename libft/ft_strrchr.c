/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:10:03 by anovoa            #+#    #+#             */
/*   Updated: 2024/01/30 13:22:44 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				last_i;
	unsigned char	ch;

	i = 0;
	last_i = -1;
	ch = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == ch)
			last_i = i;
		i++;
	}
	if (s[i] == ch)
		last_i = i;
	if (last_i == -1)
		return (NULL);
	return ((char *)&s[last_i]);
}
