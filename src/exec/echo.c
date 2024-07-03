/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/07/03 19:05:14 by anovoa           ###   ########.fr       */
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

int	is_n_option(t_token *node)
{
	char	*str;

	if (node && node->token)
	{
		str = node->token;
		while (*str)
		{

		}
	}
	return (0);
}

/* This function prints the given string followed by a new line. 
 * If given the -n option, it will not add the trailing new line. 
 * Usage: receives token after "echo"
*/
//void	echo(char *options, char *str)
void	echo(t_token *head)
{
	t_token *node;

	node = head;
	if (!head || !head->token)
	{
		printf("%s", "\n");
		return ;
	}
	if (head->next && head->next->token)
	{
		while (node && node->type == 13 && is_n_option(node->next))
		{
			node = node->next->next
		}
		//parse, separate string from options
		//mb make if recursive
		printf("%s\n","here I am");
		printf("%s", head->next->token);
		if (options)
			if (options[0] == '-' && options[1] == 'n')
				printf("%c", '\n');
	}
}

t_token	*mock_builtin_tokenizer(t_token *head)
{
	if (!head)
		return (NULL);
	if (!ft_strncmp(head->token, "echo"))
	{
		printf("%s", head->token);
		echo(head->next);
	}
	return (head);
}
