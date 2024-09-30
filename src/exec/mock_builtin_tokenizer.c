/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_builtin_tokenizer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:23:03 by anovoa            #+#    #+#             */
/*   Updated: 2024/09/24 16:59:15 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function calls builtins. For test purposes only */
t_token	*mock_builtin_tokenizer(t_token *head, t_env **env)
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
	if (!ft_strcmp(head->token, "echo"))
		echo(head->next);
	else if (!ft_strcmp(head->token, "exit"))
		ft_exit(head->next);
	else if (!ft_strcmp(head->token, "env"))
		ft_env(head->next, *env);//returns errno, should put it somewhere
	return (head);
}
