/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:06:00 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 11:47:00 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		reset_heredocs(t_file *redir);

/* Executes a sequence of commands, performing redirections as required.
 * Commands joined through pipes are executed. 
 * Commands joined through && and || operators are returned, with only
 * the first command executed.
 * Exit status of the last command executed is updated to a pointer */
t_cmd	*process_command_block(t_cmd *cmd, int *err_code, t_env *tenv)
{
	pid_t	last_pid;
	pid_t	pid;
	t_pipe	fds;
	int	pos;
	t_signal	s;

	pos = 0;
	while (cmd)
	{
		/*
		if (cmd->files)
		{
			printf("pF1:%p\n", cmd->files);
			printf("pF1:%s\n", cmd->files->name);
			if (cmd->files->next)
			{
				printf("pF2:%p\n", cmd->files->next);
				printf("pF2:%s\n", cmd->files->next->name);
			}
		}
		*/
		if (cmd->connection_type == PIPE)
			safe_pipe(&fds);
		handle_update_signal(&s, SIG_HANDLE_BLCK);
		pid = safe_fork();
		if (pid == 0)
			process_child(cmd, &fds, tenv, pos);
		last_pid = pid;
		if (cmd->connection_type == PIPE || is_last_cmd_in_pipe(cmd, pos))
			update_pipes(&fds, pos, cmd->next);
		pos++;
		reset_heredocs(cmd->files);
		//if AND/OR, return CURRENT cmd but check first for subCmd
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
