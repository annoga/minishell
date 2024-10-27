/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:25:23 by angeln            #+#    #+#             */
/*   Updated: 2024/10/27 10:25:30 by angeln           ###   ########.fr       */
/*                                                                            */
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
