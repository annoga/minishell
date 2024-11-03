/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:56:32 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 14:40:30 by anovoa           ###   ########.fr       */
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
				if (status == 130)//pruébalo
					return (status);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	handle_update_signal(&s, SIG_HANDLE_BLCK);
	handle_update_signal(&s, SIG_HANDLE_EXEC);
	return (status);
}

/*int	process_hdoc_child(char *word, t_pipe *fds, int expand, t_env **tenv)
{
	t_signal	s;

	handle_update_signal(&s, SIG_HANDLE_HDOC);
	if (safe_close(fds->next[READ]) == -1)
		return (1);
	while (42)
	{
		line = readline("> ");
		if ((!line && print_hdoc_err(word)) || !ft_strcmp(line, word))
			break ;
		if (exp)
			expand_heredoc_line(line, fds->next[WRITE], *tenv);
		else
		{
			ft_putendl_fd(line, fds->next[WRITE]);
			free(line);
		}
		free(line);
	}
	exit(0);
}*/
/*
static int	print_hdoc_err(char *word)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(word, 2);
	ft_putendl_fd("')", 2);
	return (1);
}*/
