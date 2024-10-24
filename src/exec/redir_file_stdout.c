/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file_stdout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:42:21 by angeln            #+#    #+#             */
/*   Updated: 2024/10/24 13:43:41 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Opens the given filename, redirects output to it, then closes it*/
int	redir_file_stdout(char *filename, int mode)
{
	int	fd;

	fd = 0;
	if (mode == REDIR_OUT)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (mode == APPEND)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	dup2(fd, 1);//err msg?
	close(fd);
	return (0);//return exit code
}
