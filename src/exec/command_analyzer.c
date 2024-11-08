/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:53:43 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 22:46:32 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	command_analyzer(t_env **env, t_cmd *cmd)
{
	int			status;
	t_signal	s;

	status = 0;
	if (cmd)
	{
		status = get_heredocs(cmd, env, 0);
		handle_update_signal(&s, SIG_HANDLE_BLCK);
		if (status == 0)
		{
			handle_update_signal(&s, SIG_HANDLE_EXEC);
			status = ft_analyze_cmd(env, cmd, 0);
		}
	}
	handle_update_signal(&s, SIG_HANDLE_BLCK);
	(*env)->exit_status = status;
	g_mode = 0;
	handle_update_signal(&s, SIG_HANDLE_IDLE);
}
