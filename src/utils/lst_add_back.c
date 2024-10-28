/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:09:53 by crmanzan          #+#    #+#             */
/*   Updated: 2024/10/28 17:10:24 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	lst_add_back(void *lst, void *new)
{
	void	**aux;

	if (!lst || !new)
		return ;
	if (!*(void **)lst)
	{
		*(void **)lst = new;
		return ;
	}
	aux = *(void **)lst;
	while (*aux)
		aux = *aux;
	*aux = new;
}
