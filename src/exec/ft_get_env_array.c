/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:59:43 by angeln            #+#    #+#             */
/*   Updated: 2024/10/21 08:42:27 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_listlen(t_env *env);

char	**ft_get_env_array(t_env *env)
{
	int		count;
	char	**env_arr;
	int		length;
	int		i;

	count = env_listlen(env);
	env_arr = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	if (!env_arr)
		return (NULL);
	while(env)
	{
		length = ft_strlen(env->key_name) + ft_strlen(env->value) + 2;
		env_arr[i] = ft_calloc(length, sizeof(char));
		if (!env_arr[i])
			free_split(env_arr);//y retorna NULL
		env_arr[i] = env->
		env = env->next;
	}
	return (NULL);
}

int	env_listlen(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (0);
}
