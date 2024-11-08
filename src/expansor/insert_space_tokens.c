/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_space_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:16:41 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:16:43 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*allocate_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("malloc");
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

static t_token	*create_space_token(void)
{
	t_token	*space_token;

	space_token = allocate_token();
	if (!space_token)
		return (NULL);
	space_token->token = ft_strdup(" ");
	if (!space_token->token)
	{
		perror("strdup");
		free(space_token);
		return (NULL);
	}
	space_token->type = SPACE_TOKEN;
	return (space_token);
}

void	insert_space_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*space_token;
	t_token	*next;

	current = *tokens;
	if (!current)
		return ;
	while (current->next)
	{
		next = current->next;
		space_token = create_space_token();
		if (!space_token)
			return ;
		current->next = space_token;
		space_token->next = next;
		current = next;
	}
}
