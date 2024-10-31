/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:40:52 by angeln            #+#    #+#             */
/*   Updated: 2024/10/30 09:45:05 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Returns exit status */

int is_valid_key(char *key)
{
	int i = 0;

	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=' && key[i] != '+')
			return (0);
		if(key[i] == '+' && key[i + 1] == '=')
			return (0);
		i++;
	}
	return (1);
}

t_env *create_new_export(char *key, char *value)
{
	t_env *new;
	int equal_pos;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key_name = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	(void)cmd;
	(void)env;
	int i = 0;
	int j = 0;

	if(!cmd->cmd[1])
	{
		ft_env(*env);
		return (0);
	}
	else
	{
		if(!is_valid_key(cmd->cmd[1]))
		{
			printf("export: `%s': not a valid identifier\n", cmd->cmd[1]);
			return (1);
		}
		return(0);
		while(cmd->cmd[++i])
		{
			
		}
	}
	return (0);
}
