/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/10/30 00:10:19 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_redirs(t_cmd *cmd);
static void	execute_builtin(t_cmd *cmd, t_env *tenv);
static void	validate_cmdpath(char *cmd);

/* Can fit in analze_cmd */
int	process_child(t_cmd *cmd, t_pipe *fds, t_env *tenv, int cmd_index)
{
	int		err_code;
	char	**env;

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
	execute_builtin(cmd, tenv);
	//printf("I'm about to execute things\n");
	validate_cmdpath(cmd->path);
	env = tenv_to_array(tenv);
	execve(cmd->path, cmd->cmd, env);// No se están retornando:
	exit(1);
	return (0);
}

	/*char	**env_arr;
	env_arr = tenv_to_array(env);//need to free_split when done
	if (!env_arr)
	{
		printf("error translating t_env\n");
		return (0);
	}*/

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

/* If a given command matches a builtin, it runs the builtin. Then,
 * the process is killed. Otherwise, it does nothing */
static void	execute_builtin(t_cmd *cmd, t_env *tenv)
{
	 int	err_code;

	err_code = 0;
	if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "echo"))
	{
		err_code = echo(cmd);
		exit(err_code);
	}
	else if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "pwd"))
	{
		err_code = ft_pwd(cmd);
		exit(err_code);
	}
	else if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "env"))
		ft_env(tenv);
	//else if (!ft_strcmp(head->token, "env"))
		//ft_env(head->next, *env);//returns errno, should put it somewhere
//	else if (!ft_strcmp(cmd->cmd[0], "exit"))
//		err_code = ft_exit(head->next);
}

/* Exits with the corresponding error, when applicable:
 * Command does not exist: 127 
 * Command does not have execution permissions: 126
 * Command points to a directory: 126 */
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
