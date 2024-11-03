/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:42:30 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 17:42:56 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_cmd	*add_command(t_cmd **cmd_lst)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(t_cmd), 1);
	if (!command)
	{
		lstclear(cmd_lst, del_command);
		return (NULL);
	}
	lst_add_back(cmd_lst, command);
	return (command);
}
