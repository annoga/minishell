/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_write_stdout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:26:07 by angeln            #+#    #+#             */
/*   Updated: 2024/10/24 13:26:26 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Links standard output to our pipe's input */
void	pipe_write_stdout(int *pipe)
{
	close(pipe[READ]);
	dup2(pipe[WRITE], 1);
	close(pipe[WRITE]);
}
