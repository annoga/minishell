/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:49:33 by crmanzan          #+#    #+#             */
/*   Updated: 2024/05/30 21:50:57 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

t_token	*get_special_token(char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|')
		return (create_token(OR, "||", i));
	else if (line[*i] == '|')
		return (create_token(PIPE, "|", i));
	else if (line[*i] == '&' && line[*i + 1] == '&')
		return (create_token(AND, "&&", i));
	return (NULL);
}

t_token	*get_token(char *line, int *i, int is_paren)
{
	t_token	*token;

	token = get_special_token(line, i);
	if (token)
		return (token);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		token = create_token(HEREDOC, "<<", i);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		token = create_token(APPEND, ">>", i);
	else if (line[*i] == '<')
		token = create_token(REDIR_IN, "<", i);
	else if (line[*i] == '>')
		token = create_token(REDIR_OUT, ">", i);
	else if (line[*i] == '\'')
		token = handle_single_quote(line, i);
	else if (line[*i] == '"')
		token = handle_double_quote(line, i);
	else if (ft_isspace(line[*i]))
		token = handle_space(line, i);
	else if ((line[*i] == '(' || line[*i] == ')'))
		token = handle_parenthesis(line, i, is_paren);
	else
		token = handle_arg(line, i);
	return (token);
}

t_token	*tokenizer(char *line)
{
	t_token	*head_token;
	t_token	*token;
	int		i;

	head_token = NULL;
	i = 0;
	while (line[i])
	{
		token = get_token(line, &i, 0);
		if (!token)
			return (NULL);
		add_token(&head_token, token);
		i++;
	}
	return (head_token);
}
