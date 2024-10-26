/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/10/26 20:30:14 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Can fit in analze_cmd */
int	exec_child(t_cmd *cmd, t_pipe fds, char *env[], int j)
{
	if (cmd->connection_type == PIPE)
	{
		printf("kid - read:%i, write:%i\n",fds.next[READ],fds.next[WRITE]);
	//command n0: dup input
	//command n0: dup input
		if (j != 0)//movemos IN salvo en el primero
			pipe_read_stdin(fds.next);
	//command ...(n - 1): dup output
		if (j == 0 || cmd->next)//movemos OUT salvo en el último (no PIPE)
			pipe_write_stdout(fds.next);
	}
//	if (j >= 0)//
//		j++;//
	if (cmd->files && cmd->files->type == REDIR_OUT)
		redir_file_stdout(cmd->files->name, REDIR_OUT);
	if (cmd->files && cmd->files->type == APPEND)
		redir_file_stdout(cmd->files->name, APPEND);
	execve(cmd->path, cmd->cmd, env);
	exit(1);
}
//redir a ficheros desde PIPE necesitaría tomar la pipe en cuenta, no?
//estoy cerrando la PIPE correctamente en el último comando?
