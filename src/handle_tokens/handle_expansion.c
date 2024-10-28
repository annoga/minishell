/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 handle_expansion.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/28 17:45:48 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/10/28 17:47:37 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*handle_no_expansion(char *line, int *i)
{
	int		start;
	char	*value;

	start = ++*i;
	if (line[*i] == '?')
		return (new_token(EXIT_STATUS, ft_strdup("$?")));
	while (line[*i] && !ft_istoken(line[*i]) && !ft_isalpha(line[*i])
		&& line[*i] != ' ')
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		if (line[*i] == '$' && (ft_isalpha(line[*i + 1]) || line[*i + 1] == '_'
				|| line[*i + 1] == '?'))
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start - 1], (*i) - start + 1);
	if (!value)
		return (NULL);
	(*i) -= 1;
	if (value[1] == '?')
		return (new_token(EXIT_STATUS, value));
	return (new_token(ARG, value));
}

t_token	*handle_special_expansion(char *line, int *i)
{
	if (line[*i + 1] == ' ' || line[*i + 1] == '\0' || line[*i + 1] == '/')
		return (new_token(ENV, ft_strdup("HOME")));
	return (handle_no_expansion(line, i));
}

t_token	*handle_expansion(char *line, int *i)
{
	int		start;
	char	*value;

	start = *i;
	if (line[start] == '~')
		return (handle_special_expansion(line, i));
	if (!ft_isalpha(line[start + 1]) && line[start + 1] != '_')
		return (handle_no_expansion(line, i));
	start = ++*i;
	while (line[*i] && (ft_isalpha(line[*i]) || line[*i] == '_'))
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	(*i)--;
	return (new_token(ENV, value));
}
