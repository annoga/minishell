/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:34:53 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 16:28:09 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

static t_token	*arg_hdoc(char *line, int *i, int start)
{
	char	*value;
	t_token	*token;

	while (line[*i] && !ft_istoken(line[*i]) && !ft_isspace(line[*i]))
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(ARG, value);
	(*i)--;
	return (token);
}

t_token	*handle_arg(char *line, int *i, int is_hdoc)
{
	int		start;
	char	*value;
	t_token	*token;

	start = *i;
	if (is_hdoc)
		return (arg_hdoc(line, i, start));
	while (line[*i] && !ft_istoken(line[*i]) && !ft_isspace(line[*i])
		&& line[*i] != '$')
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(ARG, value);
	(*i)--;
	return (token);
}
