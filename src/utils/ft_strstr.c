/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strstr.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/28 17:22:45 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/10/28 17:22:58 by crmanzan		  ###	########.fr		  */
/*																			  */
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
