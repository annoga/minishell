/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/10/27 10:19:42 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <errno.h>//

/* Can fit in analze_cmd */
int	exec_child(t_cmd *cmd, t_pipe *fds, char *env[], int j)
{
	if (cmd->connection_type == PIPE || (j != 0 && !cmd->next))
	{
//		printf("kid#%i, read:%i write:%i\n",j,fds->next[READ],fds->next[WRITE]);
		if (j != 0)//movemos IN salvo en el primero
		{
//			printf("pos:%i, linking read %i to 0",j,fds->prev[READ]);
			pipe_read_stdin(fds->prev);
		}
		if (j == 0 || cmd->next)//movemos OUT salvo en el último (no PIPE)
		{
//			printf("pos:%i, linking write %i to 1",j,fds->next[WRITE]);
			pipe_write_stdout(fds->next);
		}
	}
//	if (j >= 0)//
//		j++;//
	if (cmd->files && cmd->files->type == REDIR_OUT)
		redir_file_stdout(cmd->files->name, REDIR_OUT);
	if (cmd->files && cmd->files->type == APPEND)
		redir_file_stdout(cmd->files->name, APPEND);
	execve(cmd->path, cmd->cmd, env);// No se están retornando:
	exit(42);
	return (0);
}
