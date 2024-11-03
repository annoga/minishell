/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:56:32 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 18:27:12 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_heredocs(t_cmd *cmd, t_env **tenv, int status)
{
	t_signal	s;
	t_file		*redir;

	handle_update_signal(&s, SIG_HANDLE_BLCK);
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
