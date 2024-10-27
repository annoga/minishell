/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/10/27 22:54:53 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	validate_cmdpath(char *cmd);

/* Executes redirections for the given command.
 * Executes heredocs across all commands */
static int	process_redirs(t_cmd *cmd)
{
	if (cmd->files && cmd->files->type == REDIR_IN)
		redir_file_stdin(cmd->files->name, REDIR_IN);
	if (cmd->files && cmd->files->type == REDIR_OUT)
		redir_file_stdout(cmd->files->name, REDIR_OUT);
	if (cmd->files && cmd->files->type == APPEND)
		redir_file_stdout(cmd->files->name, APPEND);
	return (0);
	//while cmd... if cmd->files... type==HEREDOC
	//igual el heredoc se puede hacer separado
}

/* Can fit in analze_cmd */
int	process_child(t_cmd *cmd, t_pipe *fds, char *env[], int cmd_index)
{
	if (cmd->connection_type == PIPE || (cmd_index != 0 && !cmd->next))
	{
//		printf("kid#%i, read:%i write:%i\n",j,fds->next[READ],fds->next[WRITE]);
		if (cmd_index != 0)//movemos IN salvo en el primero
		{
//			printf("pos:%i, linking read %i to 0",j,fds->prev[READ]);
			pipe_read_stdin(fds->prev);
		}
		//movemos OUT salvo en el último (no PIPE)
		if (cmd_index == 0 || cmd->next)
		{
//			printf("pos:%i, linking write %i to 1",j,fds->next[WRITE]);
			pipe_write_stdout(fds->next);
		}
	}
//	if (j >= 0)//
//		j++;//
	process_redirs(cmd);
/*	if (cmd->files && cmd->files->type == REDIR_OUT)
		redir_file_stdout(cmd->files->name, REDIR_OUT);
	if (cmd->files && cmd->files->type == APPEND)
		redir_file_stdout(cmd->files->name, APPEND);*/
	validate_cmdpath(cmd->path);
	execve(cmd->path, cmd->cmd, env);// No se están retornando:
	exit(1);
	return (0);
}

/* Exits with the corresponding error, when applicable:
 * Command does not exist: 127 
 * Command does not have execution permissions: 126
 * Command points to a directory: 126
 * */
static void	validate_cmdpath(char *cmd)
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
