/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/07/11 11:37:44 by anovoa           ###   ########.fr       */
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
void	echo(t_token *head)
{
	t_token	*nextn;
	int		has_n;

	has_n = 0;
	if (head)
		nextn = head->next;
	if (!head || !head->token || !head->next)
		printf("%s", "\n");
	else if (token_exists(nextn))
	{
		while (head && head->type == 13 && has_n_option(nextn))
		{
			has_n = 1;
			head = nextn->next;
			if (!head)
				break ;
			nextn = head->next;
		}
		while (head && token_exists(nextn) && printf("%s", nextn->token))
			nextn = nextn->next;
		if (!has_n)
			printf("%c", '\n');
	}
}
