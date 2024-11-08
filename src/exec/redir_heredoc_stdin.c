/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_stdin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:51:31 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 16:40:47 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redir_heredoc_stdin(int fd)
{
	if (fd == -1)
		return (0);
	if (safe_dup2(fd, 0) == -1)
		return (1);
	if (safe_close(fd) == -1)
		return (1);
	return (0);
}
