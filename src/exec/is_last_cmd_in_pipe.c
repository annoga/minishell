/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_last_cmd_in_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:47:32 by angeln            #+#    #+#             */
/*   Updated: 2024/10/30 00:47:43 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Returns 1 when the given command is the last of a sequence of PIPEs. 
 * Returns 0 if there is no sequence, or if it has not ended */
int	is_last_cmd_in_pipe(t_cmd *cmd, int pos)
{
	if (pos == 0 || cmd->connection_type == PIPE)
		return (0);
	if (cmd->connection_type == AND || cmd->connection_type == OR)
		return (1);
	if (!cmd->next)
		return (1);
	return (0);
}
