/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_builtin_tokenizer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:23:03 by anovoa            #+#    #+#             */
/*   Updated: 2024/07/08 21:28:06 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function calls a builtin. For test purposes only */
t_token	*mock_builtin_tokenizer(t_token *head)
{
	if (!head)
		return (NULL);
	if (!ft_strncmp(head->token, "echo"))
		echo(head->next);
	return (head);
}
