/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:17:48 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:17:49 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd_arguments(t_cmd *cmd)
{
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-')
	{
		ft_putendl_fd("pwd: minishell does not allow options", 2);
		ft_putendl_fd("pwd: usage <\"pwd\">", 2);
		return (1);
	}
	return (0);
}

void	ft_pwd(t_cmd *cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (pwd_arguments(cmd))
	{
		free(cwd);
		exit(2);
	}
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		exit(2);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	exit(0);
}
