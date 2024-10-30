/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:53:43 by angeln            #+#    #+#             */
/*   Updated: 2024/10/30 09:33:10 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function does DEBUG stuff. For test purposes only */
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
	 
	int	status;

	status = 0;
	if (cmd)
		status = ft_analyze_cmd(env, cmd);
	printf("Last cmd exited with status %d\n", status);
	return (head);
}
