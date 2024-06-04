/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:48:15 by crmanzan          #+#    #+#             */
/*   Updated: 2024/05/30 21:48:32 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

t_token	*handle_single_quote(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = ++(*i);
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] != '\'')
	{
		printf("Error: missing quote\n");
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(SINGLE_QUOTE, value);
	return (token);
}

t_token	*handle_double_quote(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = ++(*i);
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] != '"')
	{
		printf("Error: missing quote\n");
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(DOUBLE_QUOTE, value);
	return (token);
}

t_token	*handle_parenthesis(char *line, int *i)
{
	char	*value;
	t_token	*token;

	value = ft_strndup(&line[*i], 1);
	if (!value)
		return (NULL);
	if(line[*i] == '(')
		token = new_token(L_PAREN, value);
	else if(line[*i] == ')')
		token = new_token(R_PAREN, value);
	return (token);
}

t_token	*handle_arg(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\''
		&& line[*i] != '"' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|' && line[*i] != '(' && line[*i] != ')')
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

t_token	*handle_space(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	(*i)--;
	return (create_token(SPACE_TOKEN, " ", i));
}
