#include "../../inc/minishell.h"

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
    t_env	*new;
    t_env   *tmp;

    if(!name || !value || !env)
    new = ft_calloc(1, sizeof(t_env));
    if (!new)
        return ;
    new->key_name = name;
    new->value = value;
    new->next = NULL;
    if(*env)
    {
        tmp = *env;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    else
        *env = new;
}

void env_set_value(t_env **env, char *key, char *value)
{
    t_env *old_value;

    old_value = env_get_value(*env, key);
    if(!old_value)
        env_new(env, key, value);
    else if (old_value && value)
    {
        if(old_value->value)
            free(old_value->value);
        old_value->value = value;
    }
}

int goto_dir(char *dir, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	int		res;


	oldpwd = getcwd(NULL, 0);
	res = chdir(dir);
    printf("oldpwd: %s\n", oldpwd);
    if (res == 0)
	{
		env_set_value(&env, "OLDPWD", oldpwd);
		newpwd = getcwd(NULL, 0);
		env_set_value(&env, "PWD", newpwd);
		return 0;
	}
	else
	{
		free(oldpwd);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir);
		return 1;
	}
}

int goto_home(t_env *env)
{
    char *home;

    home = ft_getenv("HOME", env);
    if(!home)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        return 1;
    }
    else
        goto_dir(home, env);
    return 0;
}

void ft_cd(t_cmd *cmd, t_env *env)
{
    if(cmd->cmd[1] != NULL)
        goto_dir(cmd->cmd[1], env);
    else
        goto_home(env);
}