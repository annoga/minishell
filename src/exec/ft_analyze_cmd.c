/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/09/25 19:55:56 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function takes one or more commands and goes through them */
int	ft_analyze_cmd(t_token *head)
{
	//while (cmd)//lista de t_cmd
	//REDIR
//	if (head->type == REDIR_IN || head->type == REDIR_OUT)
	//	ft_redir(token, fd) --> 0, 1
	//CMD
	//if (.... COMMAND)
	//	ft_check_cmd
	//	ft_do_cmd
	//PIPE
	//if (PIPE)
	//	ft_redir(token, fd) --> 0
	//...and start again
	ft_validate_cmd
	return (0);
}
