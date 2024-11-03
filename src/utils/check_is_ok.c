/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_ok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:12:42 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 16:21:50 by crmanzan         ###   ########.fr       */
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
				return (return_error("Error: missing single quote"), 0);
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (!line[i])
				return (return_error("Error: missing double quote"), 0);
		}
		i++;
	}
	return (1);
}

int	check_parenthesis(char *line)
{
	int	count;
	int	i;
	int	is_quote;

	count = 0;
	is_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			is_quote = !is_quote;
		if (line[i] == '(' && !is_quote)
			count++;
		else if (line[i] == ')' && !is_quote)
		{
			if (count == 0)
				return_error("Error: missing opening \
parenthesis");
			count--;
		}
		i++;
	}
	if (count > 0)
		ft_printf("Error: missing closing parenthesis\n");
	return (count == 0);
}

int	check_is_ok(char *line, t_env *env)
{
	if (!check_quotes(line))
	{
		env->exit_status = 2;
		return (2);
	}
	if (!check_parenthesis(line))
	{
		env->exit_status = 2;
		return (2);
	}
	return (0);
}
