/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 insert_space_tokens.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/03 19:02:23 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/03 19:02:44 by crmanzan		  ###	########.fr		  */
/*																			  */
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
	space_token->token = strdup(" ");
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
