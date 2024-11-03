/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:34:53 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 01:47:43 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*handle_arg(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = *i;
	//DOLAR CUIDADO POR SI NO GESTIONA BIEN
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
