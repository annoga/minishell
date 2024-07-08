/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/07/08 21:25:21 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Assumes strings between quotes come as a single token. Validates
 * only options of the form "-n", "-nn", "-nnn", etc */
static int	has_n_option(t_token *node)
{
	char	*str;

	if (node && node->token)
	{
		str = node->token;
		if (*str != '-')
			return (0);
		str++;
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
	}
	return (1);
}

/* Checks if a node exists and contains a token */
static int	token_exists(t_token *node)
{
	if (!node || !node->token)
		return (0);
	return (1);
}

/* This function prints the given string followed by a new line. 
 * If given the -n option, it will not add the trailing new line. 
 * Usage: receives token after "echo"
*/
int	echo(t_token *head)
{
	t_token	*node;
	t_token	*nextn;
	int		has_n;

	has_n = 0;
	if (!head || !head->token)
		return (printf("%s", "\n"));
	node = head;
	nextn = node->next;
	if (token_exists(nextn))
	{
		while (node && node->type == 13 && has_n_option(nextn))
		{
			has_n = 1;
			node = nextn->next;
			nextn = node->next;
		}
		while (token_exists(nextn) && printf("%s", nextn->token))
			nextn = nextn->next;
		if (!has_n)
			printf("%c", '\n');
	}
	return (1);
}
