/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:51:17 by crmanzan          #+#    #+#             */
/*   Updated: 2024/05/30 21:51:51 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->token = value;
	token->next = NULL;
	return (token);
}

t_token	*create_token(char type, char *value, int *i)
{
	t_token	*token;

	if (!ft_strncmp(value, ">>") || !ft_strncmp(value, "<<")
		|| !ft_strncmp(value, "&&") || !ft_strncmp(value, "||"))
		(*i)++;
	token = new_token(type, value);
	return (token);
}
