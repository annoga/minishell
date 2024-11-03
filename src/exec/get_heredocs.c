/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:56:32 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 16:06:21 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//static char *remove_quotes(char *word);
//static int	has_quotes(char *str);

//int	process_heredoc(t_file *current, t_env **tenv, int *status);
//int	process_hdoc_child(char *word, t_pipe *fds, int expand, t_env **tenv);

int	get_heredocs(t_cmd *cmd, t_env **tenv, int internal)
{
	t_signal	s;
	int			status;
	t_file		*redir;

	handle_update_signal(&s, SIG_HANDLE_BLCK);
	status = 0;
	if (internal)
		return (0);
	while (cmd && status == 0)
	{
		redir = cmd->files;
		while (redir)
		{
			if (redir && redir->type == HEREDOC)
			{
				process_heredoc(redir, tenv, &status);
				if (!cmd->cmd)
					if (clear_heredoc(redir) != 0)
						return (1);
				if (status == 130)
					return (status);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (status);
}
