/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file_stdin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:42:21 by angeln            #+#    #+#             */
/*   Updated: 2024/10/27 22:59:13 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Opens the given filename and redirects it towards the standard input */
int	redir_file_stdin(char *filename, int mode)
{
	int	fd;

	fd = 0;
	if (mode == REDIR_IN)
		fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	if (dup2(fd, 0) == -1)//err msg?
		return (1);
	if (close(fd) == -1)
		return (1);
	return (0);//return exit code
}
