/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:35:53 by crmanzan          #+#    #+#             */
/*   Updated: 2024/10/28 17:36:18 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*handle_single_quote(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = (*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
		(*i)++;
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(SINGLE_QUOTE, value);
	(*i)--;
	return (token);
}
