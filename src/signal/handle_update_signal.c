/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_update_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:05:52 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/04 23:06:31 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_signal(t_sigaction *sigact, int signal)
{
	if (sigemptyset(&(*sigact).sa_mask) == -1)
	{
		perror("sigemptyset");
		exit(EXIT_FAILURE);
	}
	if (sigaddset(&(*sigact).sa_mask, signal) == -1)
	{
		perror("sigaddset");
		exit(EXIT_FAILURE);
	}
	sigact->sa_flags = 0;
	sigaction(signal, sigact, NULL);
}

void	rl_blank_line(void)
{
	char	*original_line;
	char	*blank_line;
	size_t	len;

	original_line = ft_strdup(rl_line_buffer);
	if (!original_line)
		return ;
	len = ft_strlen(rl_line_buffer) + 2;
	blank_line = (char *)malloc(len * sizeof(char));
	if (!blank_line)
	{
		free(original_line);
		return ;
	}
	ft_memset(blank_line, ' ', len - 1);
	blank_line[len - 1] = '\0';
	rl_on_new_line();
	rl_replace_line(blank_line, 1);
	rl_redisplay();
	free(blank_line);
	rl_replace_line(original_line, 1);
	rl_redisplay();
	free(original_line);
}

void	handle_idle_signal(int signal)
{
	rl_blank_line();
	if (signal == SIGINT)
	{
		g_mode = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (ft_strlen(rl_line_buffer) <= 2)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_exec(int signal)
{
	g_mode = signal;
}

void	handle_update_signal(t_signal *signals, enum e_signal_handle mode)
{
	if (mode == SIG_HANDLE_IDLE)
		signals->ctrl_c.sa_handler = handle_idle_signal;
	else if (mode == SIG_HANDLE_HDOC)
		signals->ctrl_c.sa_handler = SIG_DFL;
	else if (mode == SIG_HANDLE_EXEC)
		signals->ctrl_c.sa_handler = sig_handler_exec;
	else if (mode == SIG_HANDLE_BLCK)
		signals->ctrl_c.sa_handler = SIG_IGN;
	else
		signals->ctrl_c.sa_handler = SIG_DFL;
	if (mode == SIG_HANDLE_HDOC)
		signals->ctrl_slash.sa_handler = SIG_IGN;
	else
		signals->ctrl_slash.sa_handler = signals->ctrl_c.sa_handler;
	init_signal(&signals->ctrl_c, SIGINT);
	init_signal(&signals->ctrl_slash, SIGQUIT);
}
