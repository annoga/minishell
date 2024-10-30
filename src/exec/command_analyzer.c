/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyzer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:23:03 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/30 01:42:37 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function calls builtins. For test purposes only */
t_token	*command_analyzer(t_token *head, t_env **env, t_cmd *cmd)
{
	if (!head)
		return (NULL);
//	debug = 1;
	 if (!ft_strcmp(head->token, "zorionak"))/*DEBUG start*/
	 {
	 	if (debug == 1)
	 		debug = 0;
	 	else
	 		debug = 1;
	 }
	if (!ft_strcmp(head->token, "cmd"))/*DEBUG start*/
	 {
	 	if (debug == 2)
	 		debug = 0;
	 	else
	 		debug = 2;
	 }
	 
	 /*DEBUG end*/
	//exit, unset, export. Any builtins that do NOT work with pipes
	if (!ft_strcmp(head->token, "exit"))
		ft_exit(head->next);
	else if(!ft_strcmp(head->token, "unset"))
		ft_unset(cmd->cmd[1], env);
	else//everything else goes in here
		ft_analyze_cmd(*env, cmd);
	return (head);
}
