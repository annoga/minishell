#include "../../inc/minishell.h"

void env_set_value(t_env **env, char *key, char *value)
{
    t_env *old_value;

    old_value = env_get_value(*env, key);
    if(!old_value)
        env_new(env, key, value);
    else
    {
        if (old_value && value)
        {
            if(old_value->value)
                free(old_value->value);
            old_value->value = value;
        }
        free(key);
    }
}

int goto_dir(char *dir, t_env *env)
{
	char	*cwd;
    char    *oldpwd;
	char	*pwd;
	int		res;

	cwd = getcwd(NULL, 0);
	res = chdir(dir);
    if (res == 0)
	{
        oldpwd = ft_strdup("OLDPWD");
        if(!oldpwd)
            return 1;
		env_set_value(&env, oldpwd, cwd);
		cwd = getcwd(NULL, 0);
        pwd = ft_strdup("PWD");
        if(!pwd)
            return 1;
		env_set_value(&env, pwd, cwd);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		return (free(cwd), perror(dir), 1);
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

int ft_cd(t_cmd *cmd, t_env *env)
{
    if(cmd->cmd[1] != NULL)
        return(goto_dir(cmd->cmd[1], env));
    else
        return(goto_home(env));
}