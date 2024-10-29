/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:06:00 by angeln            #+#    #+#             */
/*   Updated: 2024/10/29 23:52:29 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		safe_pipe(t_pipe *fds);
static int		is_last_cmd_in_pipe(t_cmd *cmd, int pos);
static pid_t	wait_for_status(pid_t last_pid, int n);

t_cmd	*process_command_block(t_cmd *cmd, int *err_code, t_env *tenv)
{
	pid_t	last_pid;
	pid_t	pid;
	t_pipe	fds;
	int	j;

	j = 0;


	while (cmd)
	{
		if (cmd->connection_type == PIPE)
			safe_pipe(&fds);
		pid = safe_fork();
		if (pid == 0)
			process_child(cmd, &fds, tenv, j);
		last_pid = pid;
		if (cmd->connection_type == PIPE || is_last_cmd_in_pipe(cmd, j))
			update_pipes(&fds, j, cmd->next);
		j++;
		if (cmd->connection_type == AND || cmd->connection_type == OR)
		{
			cmd = cmd->next;//return (cmd);
			break ;
		}
		else
			cmd = cmd->next;
	}

	*err_code = wait_for_status(last_pid, j);
	printf("Last cmd exited with status %d\n", *err_code);
	//free_split(env_arr);
	return (cmd);
}

/* Protects the pipe command. In case of failure, prints the relevant 
 * error to STDERR and exits */
static void	safe_pipe(t_pipe *fds)
{
	if (pipe(fds->next) == -1)
	{
		perror("minishell: pipe");
		exit(1);
	}
}

/* Returns 1 when the given command is the last of a sequence of PIPEs. 
 * Returns 0 if there is no sequence, or if it has not ended */
static int	is_last_cmd_in_pipe(t_cmd *cmd, int pos)
{
	if (pos == 0 || cmd->connection_type == PIPE)
		return (0);
	if (cmd->connection_type == AND || cmd->connection_type == OR)
		return (1);
	if (!cmd->next)
		return (1);
	return (0);
}

/* Waits for n children processes to end.
 * Returns the exit status of process last_pid.
 * If process is interrupted by a signal, 128 is added as per convention */
static pid_t	wait_for_status(pid_t last_pid, int n)
{
	int		exit_status;
	int		stat_loc;
	pid_t	pid;
	int		i;

	i = 0;
	exit_status = 0;
	while (i++ < n)
	{
		pid = waitpid(-1, &stat_loc, 0);
		if (pid == last_pid)
			exit_status = stat_loc;
	}
	if (WIFSIGNALED(exit_status))
		exit_status = WTERMSIG(exit_status) + 128;
	else if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	return (exit_status);
}

