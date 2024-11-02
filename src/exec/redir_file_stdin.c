/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file_stdin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:42:21 by angeln            #+#    #+#             */
/*   Updated: 2024/11/02 22:21:51 by anovoa           ###   ########.fr       */
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
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	if (dup2(fd, 0) == -1)//err msg?
		return (1);
	if (close(fd) == -1)
		return (1);
	return (0);//return exit code
}
