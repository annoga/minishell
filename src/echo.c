/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:55:00 by angeln            #+#    #+#             */
/*   Updated: 2024/05/29 16:34:57 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function prints the given string followed by a new line. 
 * If given the -n option, it will not add the trailing new line. */
void	echo(char *options, char *str)
{
	if (str)
		printf("%s", str);
	if (options)
		if (options[0] == '-' && options[1] == 'n')
			printf("%c", '\n');
}
