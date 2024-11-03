/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:38:30 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 11:46:37 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Waits for n children processes to end.
 * Returns the exit status of process last_pid.
 * If process is interrupted by a signal, 128 is added as per convention */
int	wait_for_status(pid_t last_pid, int n)
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
		if (pid == -1)
		{
			perror("minishell: waitpid");
			exit(1);
		}
		if (pid == last_pid)
			exit_status = stat_loc;
	}
	if (WIFSIGNALED(exit_status))
		exit_status = WTERMSIG(exit_status) + 128;
	else if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	return (exit_status);
}

