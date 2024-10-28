/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:48:15 by crmanzan          #+#    #+#             */
/*   Updated: 2024/10/28 17:45:13 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*handle_parenthesis(char *line, int *i)
{
	char	*value;
	t_token	*token;

	token = NULL;
	value = ft_strndup(&line[*i], 1);
	if (!value)
		return (NULL);
	if (line[*i] == '(')
		token = new_token(L_PAREN, value);
	else if (line[*i] == ')')
		token = new_token(R_PAREN, value);
	return (token);
}
