/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hdoc_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:01:38 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 13:21:16 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	expand_heredoc_line(char *line, int fd, t_env **tenv);
static int	print_hdoc_err(char *word);

int	process_hdoc_child(char *word, t_pipe *fds, int expand, t_env **tenv)
{
	t_signal	s;
	char		*line;

	handle_update_signal(&s, SIG_HANDLE_HDOC);
	if (safe_close(fds->next[READ]) == -1)
		return (1);
	while (42)
	{
		line = readline("> ");
		if ((!line && print_hdoc_err(word))) 
			break ;
		if (!ft_strcmp(line, word))
		{
			free(line);
			break ;
		}
		if (expand)
			expand_heredoc_line(line, fds->next[WRITE], tenv);
		else
			ft_putendl_fd(line, fds->next[WRITE]);
		free(line);
	}
	if (safe_close(fds->next[WRITE]) == -1)
		exit(1);
	exit(0);
}

static void	expand_heredoc_line(char *line, int fd, t_env **tenv)
{
	t_token	*token;
	t_token	*tmp;

	token = tokenizer(line, *tenv);
	if (!token)
		print_and_kill("minishell: malloc", 1);
	token = expansor(token, tenv, 1, 0);
	tmp = token;
	while (tmp)
	{
		ft_putstr_fd(tmp->token, fd);
		tmp = tmp->next;
	}
	free_token(&token);
	tmp = NULL;
	ft_putchar_fd('\n', fd);
}

static int	print_hdoc_err(char *word)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(word, 2);
	ft_putendl_fd("')", 2);
	return (1);
}
