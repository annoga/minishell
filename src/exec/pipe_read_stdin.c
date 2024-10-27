/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_read_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:25:08 by angeln            #+#    #+#             */
/*   Updated: 2024/10/24 13:26:24 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Links standard input to our pipe's output */
void	pipe_read_stdin(int *pipe)
{
	close(pipe[WRITE]);
	dup2(pipe[READ], 0);
	close(pipe[READ]);
}
