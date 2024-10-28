/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 sort_alphabetic_order.c							:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/28 17:11:40 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/10/28 17:11:40 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	case_insensitive_strcmp(const char *a, const char *b)
{
	while (*a && *b)
	{
		if (ft_tolower((unsigned char)*a) != ft_tolower((unsigned char)*b))
			return (ft_tolower((unsigned char)*a) - \
				ft_tolower((unsigned char)*b));
		a++;
		b++;
	}
	return (ft_tolower((unsigned char)*a) - ft_tolower((unsigned char)*b));
}

void	swap_tokens(t_token *a, t_token *b)
{
	char	*temp;

	temp = a->token;
	a->token = b->token;
	b->token = temp;
}

void	sort_alphabetic_token(t_token *head)
{
	int		swapped;
	t_token	*ptr1;
	t_token	*lptr;

	swapped = 1;
	lptr = NULL;
	if (head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (case_insensitive_strcmp(ptr1->token, ptr1->next->token) > 0)
			{
				swap_tokens(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
