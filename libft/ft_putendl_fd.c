/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:08:56 by anovoa            #+#    #+#             */
/*   Updated: 2024/01/30 14:19:46 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	res;

	res = ft_putstr_fd(s, fd);
	if (res == -1 || ft_putchar_fd('\n', fd) == -1)
		return (-1);
	else
		return (res + 1);
}
