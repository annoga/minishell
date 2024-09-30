/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_lstclear.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <crmanzan@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/04/30 18:36:24 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/04/30 18:36:24 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*next;

	if (*lst && lst && del)
	{
		tmp = *lst;
		while (tmp)
		{
			next = tmp->next;
			del(tmp->content);
			free(tmp);
			tmp = next;
		}
		*lst = NULL;
	}
}
