/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 export_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/03 20:03:51 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/03 20:03:51 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			if (!ft_strcmp(tmp->key_name, "SHLVL")
				&& !ft_strcmp(tmp->value, "1 "))
				printf("declare -x %s=\"1\"\n", tmp->key_name);
			else
				printf("declare -x %s=\"%s\"\n", tmp->key_name, tmp->value);
		}
		else
			printf("declare -x %s\n", tmp->key_name);
		tmp = tmp->next;
	}
}

int	not_valid_key(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || !*str)
		return (1);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+'
			&& str[i] != '=')
			return (1);
		if (str[i] == '+' && str[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_equal_position(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static int	is_addition(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	set_equal_value(t_env *env, char *str, int equal_pos)
{
	env->value = ft_strdup(str + equal_pos + 1);
	if (!env->value)
		return ;
	if (!is_addition(str))
	{
		env->key_name = ft_substr(str, 0, equal_pos);
	}
	else if (is_addition(str))
	{
		env->addition = 1;
		env->key_name = ft_substr(str, 0, equal_pos - 1);
	}
}
