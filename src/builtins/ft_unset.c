/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:18:04 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 10:48:50 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	erase_two(t_env **head, t_env *to_erase);
static void	free_two_env(t_env *env);
static int	unset_one(t_cmd *cmd, t_env ***env, int i);

int	ft_unset(t_cmd *cmd, t_env **env)
{
	t_cmd	*tmp;
	int		i;

	i = 1;
	if (!cmd || !cmd->cmd[1])
		return (0);
	tmp = cmd;
	while (tmp->cmd[i])
		unset_one(tmp, &env, i++);
	return (0);
}

static int	unset_one(t_cmd *cmd, t_env ***env, int i)
{
	t_env	*tmp;
	t_env	*next;

	tmp = **env;
	if (!cmd || !cmd->cmd[i])
		return (0);
	while (tmp)
	{
		next = tmp->next;
		if (ft_strcmp(tmp->key_name, cmd->cmd[i]) == 0)
		{
			erase_two(*env, tmp);
			return (1);
		}
		tmp = next;
	}
	return (0);
}

static void	free_two_env(t_env *env)
{
	if (env)
	{
		free(env->key_name);
		env->key_name = NULL;
		free(env->value);
		env->value = NULL;
		free(env);
	}
}

static void	erase_two(t_env **head, t_env *to_erase)
{
	t_env	*aux;
	t_env	*prev;

	if (!head || !*head || !to_erase)
		return ;
	if (*head == to_erase)
	{
		*head = to_erase->next;
		free_two_env(to_erase);
		return ;
	}
	prev = *head;
	aux = (*head)->next;
	while (aux)
	{
		if (aux == to_erase)
		{
			prev->next = aux->next;
			free_two_env(aux);
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}
