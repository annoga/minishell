/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:39:04 by anovoa            #+#    #+#             */
/*   Updated: 2024/03/09 02:19:02 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_all(char **str, unsigned int j)
{
	size_t	i;

	i = 0;
	while (i < j)
		free(str[i++]);
	free(str);
}

size_t	ft_countwords(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (str[0] && (str[0] != c))
		count++;
	while (str[0] && str[++i])
	{
		if ((str[i - 1] == c) && (str[i] != c))
			count++;
	}
	return (count);
}

static char	*ft_get_word(const char *s, char c, unsigned int *k)
{
	char			*pos;
	char			*word;
	unsigned int	len;

	len = 0;
	pos = ft_strchr(&(s[*k]), c);
	if (!pos)
		len = ft_strlen(s);
	else
		len = pos - &s[*k];
	word = ft_substr(s, *k, len);
	if (!word)
		return (NULL);
	if (!pos)
	{
		while (s[*k])
			(*k)++;
	}
	else
		*k += len;
	return (word);
}

static char	**ft_fill(char **split, char const *s, char c, unsigned int *k)
{
	unsigned int	j;

	j = 0;
	while (s[*k])
	{
		if (s[*k] == c)
			(*k)++;
		else
		{
			split[j] = ft_get_word(s, c, k);
			if (split[j++] == NULL)
			{
				ft_free_all(split, j - 1);
				return (NULL);
			}
		}
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char			**split;
	unsigned int	i;
	unsigned int	*i_ptr;

	i = 0;
	i_ptr = &i;
	split = (char **)malloc(sizeof(s) * (ft_countwords(s, c) + 1));
	if (!split || (ft_fill(split, s, c, i_ptr) == NULL))
		return (NULL);
	return (split);
}
/*#include <stdio.h>
int	main(void)
{
	char const	str[] = "Alba;Andrea;Antonia;Cora;Gerard;Raquel";
	char		c = ';';
	char		**res;
	res = ft_split(str, c);
	printf("Compi de piso que empieza por C: %s",res[3]);
	return (0);
}*/
