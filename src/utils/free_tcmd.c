/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:43:10 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 16:20:53 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*free_tfile(t_file **file_list);

char	*free_tcmd(t_cmd **cmd_list)
{
	t_cmd	*tmp;

	while (*cmd_list)
	{
		tmp = *cmd_list;
		*cmd_list = (*cmd_list)->next;
		free_split(tmp->cmd);
		tmp->cmd = NULL;
		free_tfile(&(tmp->files));
		tmp->files = NULL;
		if (tmp->subcommand)
			free_tcmd(&(tmp->subcommand));
		free(tmp);
		tmp = NULL;
	}
	free(*cmd_list);
	*cmd_list = NULL;
	return (NULL);
}

static char	*free_tfile(t_file **file_list)
{
	t_file	*tmp;

	while (*file_list)
	{
		tmp = *file_list;
		*file_list = (*file_list)->next;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp);
	}
	free(*file_list);
	*file_list = NULL;
	return (NULL);
}
