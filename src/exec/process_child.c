/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/10/28 19:31:04 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	validate_cmdpath(char *cmd);

/* Executes redirections for the given command.
 * Executes heredocs across all commands */
static int	process_redirs(t_cmd *cmd)
{
	int	err_code;
	
	err_code = 0;
	if (cmd->files && cmd->files->type == REDIR_IN)
		err_code = redir_file_stdin(cmd->files->name, REDIR_IN);
	if (cmd->files && cmd->files->type == REDIR_OUT)
		err_code = redir_file_stdout(cmd->files->name, REDIR_OUT);
	if (cmd->files && cmd->files->type == APPEND)
		err_code = redir_file_stdout(cmd->files->name, APPEND);
	return (err_code);
	//while cmd... if cmd->files... type==HEREDOC
	//igual el heredoc se puede hacer separado
}

static void	execute_builtin(t_cmd *cmd)
{
	 int	err_code;

	err_code = 0;
	if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "echo"))
	{
		err_code = echo(cmd);
		exit(err_code);
	}
	else if(cmd->cmd && !ft_strcmp(cmd->cmd[0], "pwd"))
	{
		err_code = ft_pwd(cmd);
		// free_tcmd(&cmd);
		exit(err_code);
	}
//	else if (!ft_strcmp(cmd->cmd[0], "env"))
//	{
//		err_code = ft_env(head->next, *env);
//		exit(err_code);
//	}
//	else if (!ft_strcmp(cmd->cmd[0], "exit"))
//		err_code = ft_exit(head->next);
}

/* Can fit in analze_cmd */
int	process_child(t_cmd *cmd, t_pipe *fds, char *env[], int cmd_index)
{
	int	err_code;

	err_code = 0;
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
	err_code = process_redirs(cmd);
	if (err_code != 0 || !cmd->cmd)
		exit(err_code);
	//if (!cmd->cmd)//Falta considerar subCommandos
		//exit(0);
/*	if (cmd->files && cmd->files->type == REDIR_OUT)
		redir_file_stdout(cmd->files->name, REDIR_OUT);
	if (cmd->files && cmd->files->type == APPEND)
		redir_file_stdout(cmd->files->name, APPEND);*/
	(void)env;
	execute_builtin(cmd);
	//printf("I'm about to execute things\n");
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
