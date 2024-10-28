/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:49:33 by crmanzan          #+#    #+#             */
/*   Updated: 2024/10/28 17:27:13 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*tokenizer(char *line)
{
	t_token	*head_token;
	t_token	*token;
	int		i;

	head_token = NULL;
	i = 0;
	while (line[i])
	{
		token = get_token(line, &i);
		if (!token)
			return (NULL);
		add_token(&head_token, token);
		i++;
	}
	return (head_token);
}
