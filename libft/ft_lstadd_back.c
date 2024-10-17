/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_lstadd_back.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <crmanzan@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/04/30 18:05:30 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/04/30 18:05:30 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
		*lst = new;
	else if (lst && new)
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}
