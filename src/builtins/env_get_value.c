/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:55:07 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 21:55:22 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_env	*env_get_value(t_env *var, char *name)
{
	while (var)
	{
		if (!ft_strncmp(var->key_name, name, ft_strlen(name) + 1))
			return (var);
		var = var->next;
	}
	return (NULL);
}
