/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/06/23 19:24:14 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This should go in our libft, but first check it is correct */
int	ft_strcmp(const char *s1, const char *s2)
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
}

t_token	*mock_builtin_tokenizer(t_token *head)
{
	if (!head)
		return (NULL);
	if (!ft_strmcp(head->token, "echo"))
		echo(head->next);
	
}

/* This function prints the given string followed by a new line. 
 * If given the -n option, it will not add the trailing new line. 
 * Usage: receives token after "echo"
*/
//void	echo(char *options, char *str)
void	echo(t_token *head)
{
	if (!head)
		printf("%s", "\n");
		return ;
	if (str)
		printf("%s", str);
	if (options)
		if (options[0] == '-' && options[1] == 'n')
			printf("%c", '\n');
}
