/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_whole_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:00:42 by anovoa            #+#    #+#             */
/*   Updated: 2024/02/21 20:19:12 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	resize_mem(char **current_block, size_t mul)
{
	char	*new;

	new = (char *)ft_calloc(mul * BUFFER_SIZE + 1, sizeof(char));
	if (!new)
		return (0);
	ft_strlcpy(new, *current_block, ft_strlen(*current_block) + 1);
	free(*current_block);
	*current_block = new;
	return (1);
}

void	ft_read(char **tmp, int fd, int mul)
{
	int	n_bytes;
	int	i;

	n_bytes = -1;
	i = 0;
	while (n_bytes != 0)
	{
		n_bytes = read(fd, *tmp + i, BUFFER_SIZE);
		if (n_bytes == -1 || (n_bytes == 0 && i == 0))
			ft_reset(tmp);
		i += n_bytes;
		if ((i + BUFFER_SIZE) > (mul * BUFFER_SIZE))
		{
			mul += 2;
			if (!resize_mem(tmp, mul))
				ft_reset(tmp);
		}
	}
	(*tmp)[i] = '\0';
}

char	*get_whole_file(int fd)
{
	char	*tmp;
	char	*res;

	if (fd < 0 || fd > MAX_FD - 1 || BUFFER_SIZE < 0)
		return (NULL);
	tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	ft_read(&tmp, fd, 1);
	if (!tmp)
		return (NULL);
	res = ft_substr(tmp, 0, ft_strlen(tmp));
	free(tmp);
	return (res);
}
