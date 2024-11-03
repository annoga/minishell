/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:06:00 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 21:39:11 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		reset_heredocs(t_file *redir);

/* Executes a sequence of commands, performing redirections as required.
 * Commands joined through pipes are executed. 
 * Commands joined through && and || operators are returned, with only
 * the first command executed.
 * Exit status of the last command executed is updated to a pointer */
t_cmd	*process_command_block(t_cmd *cmd, int *err_code, t_env *tenv, int pos)
{
	pid_t		last_pid;
	t_pipe		fds;
	t_signal	s;

	while (cmd)
	{
		if (cmd->connection_type == PIPE)
			safe_pipe(&fds);
		handle_update_signal(&s, SIG_HANDLE_BLCK);
		last_pid = safe_fork();
		if (last_pid == 0)
			process_child(cmd, &fds, tenv, pos);
		if (cmd->connection_type == PIPE || is_last_cmd_in_pipe(cmd, pos))
			update_pipes(&fds, pos, cmd->next);
		pos++;
		reset_heredocs(cmd->files);
		if (cmd->connection_type == AND || cmd->connection_type == OR)
			break ;
		else
			cmd = cmd->next;
	}
	*err_code = wait_for_status(last_pid, pos);
	handle_update_signal(&s, SIG_HANDLE_IDLE);
	return (cmd);
}

static int	reset_heredocs(t_file *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
			if (clear_heredoc(redir))
				return (1);
		redir = redir->next;
	}
	return (0);
}
