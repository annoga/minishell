/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 push_midlist.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/03 19:42:25 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/03 19:42:25 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	add_top(t_token *head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	tmp = head->next;
	head->next = new;
	while (new->next)
		new = new->next;
	new->next = tmp;
}

void	free_single_token(t_token *token)
{
	if (token)
	{
		free(token->token);
		token->token = NULL;
		free(token);
	}
}

void	erase_one(t_token **head, t_token *to_erase)
{
	t_token	*aux;
	t_token	*prev;

	if (!head || !*head || !to_erase)
		return ;
	if (*head == to_erase)
	{
		*head = to_erase->next;
		free_single_token(to_erase);
		return ;
	}
	prev = *head;
	aux = (*head)->next;
	while (aux)
	{
		if (aux == to_erase)
		{
			prev->next = aux->next;
			free_single_token(aux);
			aux = NULL;
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}
