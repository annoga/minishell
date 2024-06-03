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

t_token	*handle_parenthesis(char *line, int *i, int is_paren)
{
	int		start;
	char	*value;
	t_token	*token;

	printf("is_paren: %d\n", is_paren);
	if (is_paren)
		return (return_error("Syntax error near unexpected token '('"));
	if (line[*i] == ')')
		return (return_error("Syntax error near unexpected token ')'"));
	if (line[*i + 1] == '(')
		return (NULL);
	start = ++(*i);
	while (line[*i] && line[*i] != ')')
		(*i)++;
	if (line[*i] != ')')
		return (return_error("Syntax error near unexpected token '('"));
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(PAREN, value);
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
		&& line[*i] != '|')
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
	printf("space\n");
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	(*i)--;
	return (create_token(SPACE_TOKEN, " ", i));
}
