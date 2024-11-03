/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:43:48 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 17:43:54 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

static void	del_file(void *file)
{
	free(((t_file *)file)->name);
}

void	del_command(void *command)
{
	t_cmd	*tmp;

	if (!command)
		return ;
	tmp = command;
	free_split(tmp->cmd);
	lstclear(&tmp->files, del_file);
	lstclear(&tmp->subcommand, del_command);
}
