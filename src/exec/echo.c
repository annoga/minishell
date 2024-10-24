/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/09/24 17:08:32 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	has_n_option(t_cmd *node);
static int	token_exists(t_cmd *node);

/* This function prints the given string followed by a new line. 
 * If given the -n option, it will not add the trailing new line. 
 * Usage: receives token after "echo"
*/
void	echo(t_cmd *head)
{
	t_cmd	*nextn;
	int		has_n;
	int		i;

	i = 0;
	has_n = 0;
	if (head)
		nextn = head->next;
	if (!head || !head->cmd || !head->cmd[i])
		printf("%s", "\n");
	else if (token_exists(nextn))
	{
		while (head && has_n_option(nextn))
		{
			has_n = 1;
			head = nextn->next;
			if (!head)
				break ;
			nextn = head->next;
		}
		while (head && token_exists(nextn) && printf("%s", nextn->cmd[i]))
			i++;
		if (!has_n)
			printf("%c", '\n');
	}
}

/* Checks if a node exists and contains a token */
static int	token_exists(t_cmd *node)
{
	if (!node || !node->cmd)
		return (0);
	return (1);
}

/* Assumes strings between quotes come as a single token. Validates
 * only options of the form "-n", "-nn", "-nnn", etc */
static int	has_n_option(t_cmd *node)
{
	char	*str;

	if (node && node->cmd)
	{
		str = ft_strdup("hola");
		// str = node->cmd;
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
