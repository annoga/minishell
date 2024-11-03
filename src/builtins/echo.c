/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 19:57:36 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	echo_options(t_cmd next, int *has_n, int *i);
static int	has_n_option(char *str);

/* Prints any arguments given, followed by a '\n'.
 * Option -n foregoes the trailing '\n' */
void	echo(t_cmd *head)
{
	t_cmd	*nextn;
	int		has_n;
	int		i;

	i = 1;
	has_n = 0;
	if (!head || !head->cmd || !head->cmd[0])
		printf("%s", "\n");
	else
	{
		nextn = head;
		echo_options(*nextn, &has_n, &i);
		while (nextn->cmd[i])
		{
			printf("%s", nextn->cmd[i]);
			if (nextn->cmd && nextn->cmd[i + 1])
				printf(" ");
			i++;
		}
		if (!has_n)
			printf("%c", '\n');
	}
	exit(0);
}

/* Updates the index pointer to the position of the last valid 
 * -n optin, if any */
static void	echo_options(t_cmd next, int *has_n, int *i)
{
	while (next.cmd[*i] && has_n_option(next.cmd[*i]))
	{
		*has_n = 1;
		(*i)++;
	}
}

/* Checks if str is written in the following pattern:
 * "-n", "-nn", "-nnn", etc */
static int	has_n_option(char *str)
{
	if (str && str[0] == '-')
	{
		str++;
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}
