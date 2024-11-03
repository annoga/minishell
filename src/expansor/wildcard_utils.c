/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 wildcard_utils.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/08/13 20:42:36 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/08/13 20:42:39 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	set_params(t_wilds *params, const char *prefix, const char *suffix,
		int depth)
{
	params->prefix = prefix;
	params->suffix = suffix;
	params->depth = depth;
}

void	normalize_input(char *input)
{
	char	*src;
	char	*dst;

	dst = input;
	src = input;
	while (*src != '\0')
	{
		*dst = *src;
		if (*src == '*')
		{
			while (*(src + 1) == '*')
				src++;
		}
		src++;
		dst++;
	}
	*dst = '\0';
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	prefix_compare(const char *str, const char *prefix)
{
	return (ft_strncmp(str, prefix, ft_strlen(prefix)));
}

int	suffix_compare(const char *str, const char *suffix)
{
	size_t	len_str;
	size_t	len_suffix;

	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	if (len_str < len_suffix)
		return (1);
	return (ft_strcmp(str + len_str - len_suffix, suffix));
}
