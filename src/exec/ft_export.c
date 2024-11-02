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

int not_valid_key(char *str)
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

int  ft_equal_position(char *str)
{
	int i = 0;

	while(str[i])
	{
		if(str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
int	is_addition(char *str)
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

void env_new(t_env **env, char *name, char *value)
{
    t_env *new;
    t_env *tmp;

    if (!name || !value || !env)
        return;
    new = (t_env *)calloc(1, sizeof(t_env));
    if (!new) 
        return;
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

void set_equal_value(t_env *env, char *str, int equal_pos)
{
	env->value = ft_strdup(str + equal_pos + 1);
	if(!env->value)
		return ;

	if(!is_addition(str))
	{
		env->key_name = ft_substr(str, 0, equal_pos);
	}
	else if(is_addition(str))
	{
		env->addition = 1;
		env->key_name = ft_substr(str, 0, equal_pos - 1);
	}
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
	printf("v2:%p\n", new->key_name);
	env_set_value(env, new->key_name, new->value);
	//printf("v2:%p\n", new->value);
	free(new);
}

void print_export(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while(tmp)
	{
		if(tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key_name, tmp->value);
		else
			printf("declare -x %s\n", tmp->key_name);
		tmp = tmp->next;
	}
}


int	ft_export(t_cmd *cmd, t_env **env)
{
	int i = 1;
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
			printf("export: `%s': not a valid identifier\n", cmd->cmd[1]);
			return (1);
		}
		if(!not_valid_key(cmd->cmd[i]) && cmd->cmd[i])
		{
			new = create_new_export(cmd->cmd[i]);
			if(!new)
			{
				printf("Error: malloc failed\n");
				return (1);
			}
			printf("v1:%p\n", new);

			add_export(new, env);
		}
		i++;
	}
	return (0);
}
