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
#include "../inc/minishell.h"

void add_token(t_token **head, t_token *new)
{
	t_token *tmp;

	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new;
}

t_token *new_token(t_token_type type, char *value)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->token = value;
	token->next = NULL;
	return (token);
}

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

// int		start;
// char	*value;
// t_token	*token;

// start = *i;
// while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\''
// 	&& line[*i] != '"' && line[*i] != '<' && line[*i] != '>'
// 	&& line[*i] != '|' && line[*i] != '(' && line[*i] != ')')
// {
// 	if (line[*i] == '&' && line[*i + 1] == '&')
// 		break ;
// 	(*i)++;
// }
// value = ft_strndup(&line[start], *i - start);
// if (!value)
// 	return (NULL);
// token = new_token(ARG, value);
