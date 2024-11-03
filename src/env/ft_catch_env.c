/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_catch_env.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/03 19:47:36 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/03 19:47:36 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

static void	ft_aux_shlvl(t_env **tmp, t_env **last, int shlvl_flag)
{
	if (shlvl_flag == 0)
	{
		if (!ft_issafedup(tmp, "SHLVL", "1 "))
			exit(1);
		(*last)->next = *tmp;
		*last = *tmp;
	}
}

static void	ft_aux_envdup(t_env **tmp, char **envp, int i, char *div)
{
	*tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		exit(1);
	if (envp[i] && !ft_strcmp(envp[i], "SHLVL=1"))
	{
		free(*tmp);
		*tmp = NULL;
		return ;
	}
	div = ft_strchr(envp[i], '=');
	(*tmp)->key_name = ft_substr(envp[i], 0, (div - envp[i]));
	if (!(*tmp)->key_name)
		exit(1);
	(*tmp)->value = ft_substr(div + 1, 0, ft_strlen(div));
	if (!(*tmp)->value)
		exit(1);
}

void	totally_auxiliar(t_env **head, t_env **last, t_env **tmp)
{
	if (!*head)
		*head = *tmp;
	else
		(*last)->next = *tmp;
	*last = *tmp;
}

void	ft_full_env(char **envp, t_env **head)
{
	char	*div;
	t_env	*tmp;
	t_env	*last;
	int		i;
	int		shlvl_flag;

	div = NULL;
	tmp = NULL;
	last = NULL;
	i = 0;
	shlvl_flag = 0;
	while (envp[i])
	{
		ft_aux_envdup(&tmp, envp, i, div);
		if (!tmp)
		{
			i++;
			continue ;
		}
		ft_catch_shlvl(&tmp, &shlvl_flag);
		totally_auxiliar(head, &last, &tmp);
		i++;
	}
	ft_aux_shlvl(&tmp, &last, shlvl_flag);
	last->next = NULL;
}

void	ft_catch_env(char **envp, t_env **head)
{
	if (envp && envp[0])
		ft_full_env(envp, head);
	else
		ft_empty_env(head);
}
