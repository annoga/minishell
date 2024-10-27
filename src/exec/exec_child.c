/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/10/27 21:12:48 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <errno.h>//

static void	validate_cmd(char *cmd);

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
	//check
	//1)path exists
	//2)path is a directory
	//3)path has permissions
	validate_cmd(cmd->path);
	execve(cmd->path, cmd->cmd, env);// No se están retornando:
	exit(42);
	return (0);
}

/* Exits with the corresponding error, when applicable:
 * Command does not exist: 127 
 * Command does not have execution permissions: 126
 * Command points to a directory: 126
 * */
static void	validate_cmd(char *cmd)
{
	struct	stat	s;

	if (!cmd)
		exit(127);
	if (access(cmd, X_OK) == -1)
		exit(126);
	if (stat(cmd, &s) == 0)
		if (s.st_mode & S_IFDIR)
			exit(126);
}
