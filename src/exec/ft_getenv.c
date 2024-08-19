/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:06:38 by anovoa            #+#    #+#             */
/*   Updated: 2024/08/19 20:37:30 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Given a key, returns the value for a parameter in env.
 * If none is found, returns NULL */
char	*ft_getenv(char *key, t_env *envp)
{
	while(envp)
	{
		if (ft_strncmp(envp->key_name, key))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}