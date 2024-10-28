/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strncpy.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/28 17:20:54 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/10/28 17:20:54 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
}
