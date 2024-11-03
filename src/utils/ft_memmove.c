/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:30 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 22:55:06 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../../inc/minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	unsigned const char	*s;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (src > dst)
	{
		while (i < len && (src != 0 || dst != 0))
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (len > 0 && (src != 0 || dst != 0))
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	return (dst);
}
