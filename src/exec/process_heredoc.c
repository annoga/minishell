/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:57:52 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 13:08:36 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_heredoc(t_file *current, t_env **tenv, int *status)
{
	t_pipe	fds;
	pid_t	pid; 

	if (clear_heredoc(current) != 0)//clears old pipe
		return (1);
	safe_pipe(&fds);
	current->heredoc_fd = fds.next[READ];
	pid = safe_fork();
	if (pid == 0)
		process_hdoc_child(current->name, &fds, !current->is_quoted, tenv);
	if (safe_close(fds.next[WRITE]) == -1)
	{
		*status = 1;
		return (1);
	}
	*status = wait_for_status(pid, 1);
	if (*status != 0)
		if (clear_heredoc(current) != 0)
			*status = 1;
	return (*status);
}
