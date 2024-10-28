#include "../../inc/minishell.h"

int pwd_arguments(t_cmd *cmd)
{
    if (cmd->cmd[1] && cmd->cmd[1][0] == '-')
    {
        ft_putendl_fd("pwd: minishell does not allow options", 2);
        ft_putendl_fd("pwd: usage <\"pwd\">", 2);
        return (1);
    }
    return (0);
}

int ft_pwd(t_cmd *cmd)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if(pwd_arguments(cmd))
        return (free(cwd), 2);
    if (!cwd)
    {
        ft_putendl_fd("minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
        exit(1);
    }
    ft_putendl_fd(cwd, 1);
    free(cwd);
    return (0);
}
