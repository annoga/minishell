/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_ok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:12:42 by crmanzan          #+#    #+#             */
/*   Updated: 2024/06/17 18:12:51 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (return_error("Error: missing single quote\n"), 0);
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (!line[i])
				return (return_error("Error: missing double quote\n"), 0);
		}
		i++;
	}
	return (1);
}

int	check_parenthesis(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
			count++;
		else if (line[i] == ')')
		{
			if (count == 0)
			{
				return_error("Error: missing opening \
parenthesis\n");
				return (0);
			}
			count--;
		}
		i++;
	}
	return (count == 0);
}

int	check_is_ok(char *line)
{
	if (!check_quotes(line))
	{
		ft_printf("Error: missing quotes\n");
		return (0);
	}
	if (!check_parenthesis(line))
	{
		ft_printf("Error: missing parenthesis\n");
		return (0);
	}
	return (1);
}
