/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_special_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:28:23 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 16:23:25 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*get_special_token(char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|')
		return (create_token(OR, "||", i));
	else if ((line[*i] == '(' || line[*i] == ')'))
		return (handle_parenthesis(line, i));
	else if (line[*i] == '|')
		return (create_token(PIPE, "|", i));
	else if (line[*i] == '&' && line[*i + 1] == '&')
		return (create_token(AND, "&&", i));
	else if (line[*i] == '\'')
		return (handle_single_quote(line, i));
	else if (line[*i] == '$' || line[*i] == '~' )
		return (handle_expansion(line, i));
	return (NULL);
}
