/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:17:29 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:17:30 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_new(t_env **env, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (!name || !env)
		return ;
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	new->key_name = name;
	new->value = value;
	new->next = NULL;
	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
}

t_env	*create_new_export(char *str)
{
	t_env	*new;
	int		equal_pos;

	equal_pos = ft_equal_position(str);
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	new->addition = 0;
	if (!new)
		return (NULL);
	if (!equal_pos || str[equal_pos + 1] == '\0')
	{
		new->key_name = ft_strtrim(str, "=+");
		if (!new->key_name)
			return (NULL);
		if (equal_pos == 0)
			new->value = NULL;
		else
		{
			new->value = ft_strdup("\0");
			if (!new->value)
				return (NULL);
		}
	}
	else if (equal_pos > 0)
		set_equal_value(new, str, equal_pos);
	return (new);
}

void	add_export(t_env *new, t_env **env)
{
	t_env	*tmp;
	char	*tmp_value;

	if (!new || !env)
		return ;
	tmp = env_get_value(*env, new->key_name);
	if (tmp && new->addition == 1)
	{
		tmp_value = ft_strjoin(tmp->value, new->value);
		if (!tmp)
			return ;
		free(new->value);
		new->value = tmp_value;
	}
	env_set_value(env, new->key_name, new->value);
	free(new);
}

void	not_valid_key_error(char *str, int *err_code)
{
	*err_code = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int		i;
	int		err_code;
	t_env	*new;

	i = 1;
	err_code = 0;
	new = NULL;
	if (!cmd->cmd[1])
		return (print_export(*env), 0);
	while (cmd->cmd[i])
	{
		if (not_valid_key(cmd->cmd[i]))
			not_valid_key_error(cmd->cmd[i], &err_code);
		else if (!not_valid_key(cmd->cmd[i]) && cmd->cmd[i])
		{
			new = create_new_export(cmd->cmd[i]);
			if (!new)
				return (return_error("Error: malloc failed"), 1);
			add_export(new, env);
		}
		i++;
	}
	return (err_code);
}
