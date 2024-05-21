/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:13:54 by angeln            #+#    #+#             */
/*   Updated: 2024/02/10 00:56:06 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_reset(char **arg)
{
	free(*arg);
	*arg = NULL;
	return (NULL);
}

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

static char	*ft_read(int fd, char **buf)
{
	int		n_bytes;
	size_t	i;
	size_t	mul;

	mul = 10;
	i = ft_strlen(*buf);
	n_bytes = -1;
	while (!ft_strchr(*buf, '\n') && n_bytes != 0)
	{
		n_bytes = read(fd, *buf + i, BUFFER_SIZE);
		if (n_bytes == -1 || (n_bytes == 0 && i == 0))
			return (ft_reset(buf));
		i += n_bytes;
		if ((i + BUFFER_SIZE) > (mul * BUFFER_SIZE))
		{
			mul += 10;
			if (!resize_mem(buf, mul))
				return (ft_reset(buf));
		}
	}
	return (*buf);
}

static char	*ft_extract_ln(char **raw)
{
	char	*eol;
	char	*eof;
	size_t	size;
	char	*line;

	eol = ft_strchr(*raw, '\n');
	eof = ft_strchr(*raw, '\0');
	if (eol)
		eol++;
	else
		eol = eof;
	size = eol - *raw;
	line = (char *)ft_calloc(size + 1, sizeof(char));
	if (!line)
		return (ft_reset(raw));
	ft_strlcpy(line, *raw, size + 1);
	ft_strlcpy(*raw, *raw + size, eof - (*raw + size) + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*data[MAX_FD];
	char		*ln;

	if (fd < 0 || fd > MAX_FD - 1 || BUFFER_SIZE < 0)
		return (NULL);
	(data[fd] || (data[fd] = (char *)ft_calloc(1, sizeof(char))));
	if (!data[fd] || !resize_mem(&data[fd], 10))
		return (ft_reset(&data[fd]));
	if (!ft_read(fd, &data[fd]))
		return (ft_reset(&data[fd]));
	ln = ft_extract_ln(&data[fd]);
	if (!ln)
		return (NULL);
	return (ln);
}
