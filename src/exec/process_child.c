/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/10/30 09:43:54 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_redirs(t_cmd *cmd);
static void	execute_builtin(t_cmd *cmd, t_env *tenv);
static char	*validate_cmdpath(t_cmd *cmd, t_env *tenv);

/* Runs a single command or builtin within a fork. Handles pipes and 
 * redirections. When finished, or in case of error, the process exits 
 * with the appropriate status */
int	process_child(t_cmd *cmd, t_pipe *fds, t_env *tenv, int cmd_index)
{
	int		err_code;
	char	**env;

	err_code = 0;
	if (cmd->connection_type == PIPE || is_last_cmd_in_pipe(cmd, cmd_index))
	{
		if (cmd_index != 0)//movemos IN salvo en el primero
			pipe_read_stdin(fds->prev);
		if (cmd_index == 0 || !is_last_cmd_in_pipe(cmd, cmd_index))//cmd->next)
			pipe_write_stdout(fds->next);//no change if it enters in lastCmd...
	}
	err_code = process_redirs(cmd);
	if (err_code != 0 || !cmd->cmd)
		exit(err_code);
	execute_builtin(cmd, tenv);
	env = tenv_to_array(tenv);
	execve(validate_cmdpath(cmd, tenv), cmd->cmd, env);
	free(env);
	exit(1);
	return (0);
}

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

/* If a given command matches a builtin, it runs the builtin and
 * the process is killed. Otherwise, it does nothing.
 * Allowed builtins:
 * echo with or without -n option
 * env 
 * exit with up to 1 argument
 * export with no arguments */
static void	execute_builtin(t_cmd *cmd, t_env *tenv)
{
	if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "echo"))
		echo(cmd);
	else if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "env"))
		ft_env(tenv);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		exit(ft_exit(cmd));
	else if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))////OJO! sólo si no tiene argumentos
		exit(ft_export(cmd, &tenv));
}

/* Exits with the corresponding error, when applicable:
 * Command does not exist: 127 
 * Command does not have execution permissions: 126
 * Command points to a directory: 126 */
static char	*validate_cmdpath(t_cmd *cmd, t_env *tenv)
{
	struct	stat	s;
	char			*path;

	path = get_cmd_path(cmd->cmd[0], ft_getenv("PATH", tenv));
	if (!path)
		exit(127);
	if (access(path, X_OK) == -1)
		exit(126);
	if (stat(path, &s) == 0)
		if (s.st_mode & S_IFDIR)
			exit(126);
	return (path);
}
