/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:55:05 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 19:45:54 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_redirs(t_cmd *cmd);
static void	execute_builtin(t_cmd *cmd, t_env *tenv);
static char	*validate_cmdpath(t_cmd *cmd, t_env *tenv);
static int	print_err_path(char *cmd, char *err);

/* Runs a single command or builtin within a fork. Handles pipes and 
 * redirections. When finished, or in case of error, the process exits 
 * with the appropriate status */
int	process_child(t_cmd *cmd, t_pipe *fds, t_env *tenv, int cmd_index)
{
	int			err_code;
	char		**env;
	t_signal	s;
	char		*path;

	handle_update_signal(&s, SIG_HANDLE_DEFAULT);
	err_code = 0;
	if (cmd->connection_type == PIPE || is_last_cmd_in_pipe(cmd, cmd_index))
	{
		if (cmd_index != 0)
			pipe_read_stdin(fds->prev);
		if (cmd_index == 0 || !is_last_cmd_in_pipe(cmd, cmd_index))
			pipe_write_stdout(fds->next);
	}
	err_code = process_redirs(cmd);
	if (err_code != 0)
		exit(err_code);
	if (!cmd->cmd || !ft_strcmp(cmd->cmd[0], ""))
		exit(0);
	execute_builtin(cmd, tenv);
	env = tenv_to_array(tenv);
	path = validate_cmdpath(cmd, tenv);
	execve(path, cmd->cmd, env);
	exit(1);
	return (0);
}

/* Executes redirections for the given command */
static int	process_redirs(t_cmd *cmd)
{
	int		err_code;
	t_file	*tmp;

	err_code = 0;
	tmp = cmd->files;
	while (tmp && err_code == 0)
	{
		if (tmp->type == REDIR_IN)
			err_code = redir_file_stdin(tmp->name, REDIR_IN);
		if (tmp->type == REDIR_OUT)
			err_code = redir_file_stdout(tmp->name, REDIR_OUT);
		if (tmp->type == APPEND)
			err_code = redir_file_stdout(tmp->name, APPEND);
		if (tmp->type == HEREDOC)
			err_code = redir_heredoc_stdin(tmp->heredoc_fd);
		tmp = tmp->next;
	}
	return (err_code);
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
		exit(ft_exit(cmd, 0));
	else if (cmd->cmd && !ft_strcmp(cmd->cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		exit(ft_export(cmd, &tenv));
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		exit(0);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		exit(0);
}

/* Exits with the corresponding error, when applicable:
 * Command does not exist: 127 
 * Command does not have execution permissions: 126
 * Command points to a directory: 126 */
static char	*validate_cmdpath(t_cmd *cmd, t_env *tenv)
{
	struct stat		s;
	char			*path;

	path = get_cmd_path(cmd->cmd[0], ft_getenv("PATH", tenv));
	if (!path && !ft_strchr(cmd->cmd[0], '/'))
	{
		if (print_err_path(cmd->cmd[0], ": command not found"))
			exit(127);
	}
	else if (!path && ft_strchr(cmd->cmd[0], '/'))
		if (print_err_path(cmd->cmd[0], ": No such file or directory"))
			exit(127);
	if (access(path, X_OK) == -1)
		if (print_err_path(cmd->cmd[0], ": Permission denied"))
			exit(126);
	if (stat(path, &s) == 0)
		if (s.st_mode & S_IFDIR)
			if (print_err_path(cmd->cmd[0], ": Is a directory"))
				exit(126);
	return (path);
}

static int	print_err_path(char *cmd, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(err, 2);
	return (1);
}
