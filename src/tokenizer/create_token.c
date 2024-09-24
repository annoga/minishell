/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:51:17 by crmanzan          #+#    #+#             */
/*   Updated: 2024/07/08 20:57:08 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token *create_token(char type, char *line, int *i)
{
	char *value;
	t_token *token;

	//printf("line: %s\n", line);
	if (!ft_strcmp(line, ">>") || !ft_strcmp(line, "<<") || !ft_strcmp(line, "&&") || !ft_strcmp(line, "||"))
	{
		(*i)++;
	}
	value = ft_strdup(line);
	if (!value)
		return (NULL);
	token = new_token(type, value);
	return (token);
}
