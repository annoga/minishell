/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/07/08 21:13:14 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Substitute with existing strncmp */
/*int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}*/

int	print_token(t_token *head)
{
	if (head->token && head->next->token)
	{
		printf("%s", head->next->token);
	}
	return (0);
}

/* Assumes strings between quotes come as a single token. Validates
 * only options of the form "-n", "-nn", "-nnn", etc
 * */
int	has_n_option(t_token *node)
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

int	token_exists(t_token *node)
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

t_token	*mock_builtin_tokenizer(t_token *head)
{
	if (!head)
		return (NULL);
	if (!ft_strncmp(head->token, "echo"))
		echo(head->next);
	return (head);
}
