/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:21:09 by angeln            #+#    #+#             */
/*   Updated: 2024/10/27 09:31:49 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Updates pipes after a command has been executed. 
 * In all commands but the first, we close the pipe that fed into the 
 * previously executed command.
 * In all commands but the last, we position the pipe that will feed the 
 * next command. */
void	update_pipes(t_pipe *fds, int pos, t_cmd *next_cmd)
{
	if (pos != 0)
	{
//		printf("j:%i, p_R:%i, p_W:%i\n",pos,fds->prev[READ], fds->prev[WRITE]);
		close(fds->prev[READ]);
		close(fds->prev[WRITE]);
	}
	if (next_cmd)
	{
		fds->prev[READ] = fds->next[READ];
		fds->prev[WRITE] = fds->next[WRITE];
//		printf("j_n:%i, p_R:%i, p_W:%i\n",pos,fds->prev[READ],fds->prev[WRITE]);
	}
}
