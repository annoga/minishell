// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_export.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/30 09:40:52 by angeln            #+#    #+#             */
// /*   Updated: 2024/10/30 09:45:05 by angeln           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../inc/minishell.h"

// /* Returns exit status */

t_env	*env_get_value(t_env *var, char *name)
{
	while (var)
	{
		if (!ft_strncmp(var->key_name, name, ft_strlen(name)))
			return (var);
		var = var->next;
	}
	return (NULL);
}


void env_new(t_env **env, char *name, char *value)
{
    t_env *new;
    t_env *tmp;

    if (!name || !env)
        return;
    new = (t_env *)calloc(1, sizeof(t_env));
    if (!new)
        {return ;}
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

t_env *create_new_export(char *str)
{
	t_env *new;
	int equal_pos;

	equal_pos = ft_equal_position(str);
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	new->addition = 0;
	if (!new)
		return (NULL);
	if(!equal_pos || str[equal_pos + 1] == '\0')
	{
		new->key_name = ft_strtrim(str, "=+");
		if(!new->key_name)
			return (NULL);
		if(equal_pos == 0)
			new->value = NULL;
		else
		{
			new->value = ft_strdup("\0");
			if(!new->value)
				return (NULL);
		}
	}
	else if(equal_pos > 0)
		set_equal_value(new, str, equal_pos);
	return (new);
}

void add_export(t_env *new, t_env **env)
{
	t_env *tmp;
	char *tmp_value;

	if(!new || !env)
		return ;
	tmp = env_get_value(*env, new->key_name);
	if(tmp && new->addition == 1)
	{
		tmp_value = ft_strjoin(tmp->value, new->value);
		if(!tmp)
			return ;
		free(new->value);
		new->value = tmp_value;
	}
	env_set_value(env, new->key_name, new->value);
	free(new);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int i;
	int err_code;

	i = 1;
	err_code = 0;
	t_env *new;

	new = NULL;
	if(!cmd->cmd[1])
	{
		print_export(*env);
		return (0);
	}
	while(cmd->cmd[i])
	{
		if(not_valid_key(cmd->cmd[i]))
		{
			printf("export: `%s': not a valid identifier\n", cmd->cmd[i]);
			err_code = 1;
		}
		else if(!not_valid_key(cmd->cmd[i]) && cmd->cmd[i])
		{
			new = create_new_export(cmd->cmd[i]);
			if(!new)
			{
				printf("Error: malloc failed\n");
				return (1);
			}
			add_export(new, env);
		}
		i++;
	}
	return (err_code);
}
