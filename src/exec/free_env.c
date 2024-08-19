/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:37:17 by anovoa            #+#    #+#             */
/*   Updated: 2024/08/19 20:37:24 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Frees our copy of the env variable */
int	free_env(t_env **envp)
{
	t_env	*tmp;
	t_env	*old;

	tmp = *envp;
	while (tmp)
	{
		free(tmp->key_name);
		free(tmp->value);
		old = tmp;
		tmp = tmp->next;
		free(old);
	}
	return (1);
}
