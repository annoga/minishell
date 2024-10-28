/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:10:57 by crmanzan          #+#    #+#             */
/*   Updated: 2024/10/28 17:11:10 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	lstclear(void *list, void (*del)(void *))
{
	void	**aux;
	void	*tmp;

	if (!list || !del)
		return ;
	aux = *(void **)list;
	while (aux)
	{
		tmp = *aux;
		del(aux);
		free(aux);
		aux = tmp;
	}
	*(void **)list = NULL;
}
