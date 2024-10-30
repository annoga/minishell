/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:53:43 by angeln            #+#    #+#             */
/*   Updated: 2024/10/30 04:06:30 by angeln           ###   ########.fr       */
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
	//if (!ft_strcmp(head->token, "exit"))
		//ft_exit(head->next);
	//else if(!ft_strcmp(head->token, "unset"))//ojo que esto es segfault si te pongo "unset"
		//ft_unset(cmd->cmd[1], env);
	//else//everything else goes in here
	if (cmd)
		ft_analyze_cmd(env, cmd);
	return (head);
}
