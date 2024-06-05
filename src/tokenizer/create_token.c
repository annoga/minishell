/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:51:17 by crmanzan          #+#    #+#             */
/*   Updated: 2024/06/04 18:05:54 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token *create_token(char type, char *line, int *i)
{
//	int start;
///	char *value;
	t_token *token;

	// printf("0. line: %s, start: %d, i: %d\n", &line[start], start, *i);
//	start = *i;
	if (!ft_strncmp(line, ">>") || !ft_strncmp(line, "<<") || !ft_strncmp(line, "&&") || !ft_strncmp(line, "||"))
	{
//		value = ft_strndup(&line[start], 2);
		(*i)++;
	}
//	else
//		value = ft_strndup(&line[start], 1);
	// (*i)--;
	// printf("2. line: %s, start: %d, i: %d\n", &line[start], start, *i);
	// value = ft_strndup(&line[start], 2);
//	if (!value)
//		return (NULL);
	token = new_token(type, line);
	return (token);
}