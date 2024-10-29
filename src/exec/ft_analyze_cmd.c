/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/29 23:30:41 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		fill_cmd_paths(t_cmd *cmd, char *envpaths);

/* This function takes one or more commands and goes through them */
int	ft_analyze_cmd(t_env *env, t_cmd *cmnd)
{
//	char	*path;
	//char	**env_arr;
	// t_cmd	*cmnd;
//	int		i;//
//	i = 0;//
//	while (env_arr[i])//
//		printf("%s\n", env_arr[i++]);//print envp

	fill_cmd_paths(cmnd, ft_getenv("PATH", env));

//	printf("cmd[0]:%s\n", cmnd->cmd[0]);
//	printf("cmd[1]:%s\n", cmnd->cmd[1]);
	/*t_cmd	*tmp2;

	printf("cmd:%p\n", cmnd->cmd);
	printf("path:%s\n", cmnd->path);
	printf("next:%p\n", cmnd->next);//NULL if empty
	printf("subC:%p\n", cmnd->subcommand);//NULL if empty
	printf("files:%p\n", cmnd->files);//NULL if empty
	if (cmnd->files)
	{
	printf("conType:%i\n", cmnd->connection_type);//NULL if empty
	printf("fName:%s\n", cmnd->files->name);//
	printf("fType:%i\n", cmnd->files->type);//
	printf("fNxt:%p\n", cmnd->files->next);//
	}
	if (cmnd->next)
	{
		tmp2 = cmnd->next;
	printf("cmd2:%s\n", tmp2->cmd[0]);
	printf("path2:%s\n", tmp2->path);
	printf("next2:%p\n", tmp2->next);//NULL if empty
	printf("subC2:%p\n", tmp2->subcommand);//NULL if empty
	printf("files2:%p\n", tmp2->files);//NULL if empty
	if (cmnd->files)
	{
	printf("conType2:%i\n", cmnd->connection_type);//NULL if empty
	printf("fName2:%s\n", cmnd->files->name);//
	printf("fType2:%i\n", cmnd->files->type);//
	printf("fNxt2:%p\n", cmnd->files->next);//
	}
	}*/

	/*env_arr = ft_get_env_array(env);//need to free_split when done
	if (!env_arr)
	{
		printf("error translating t_env\n");
		return (0);
	}*/

	int		err_code;
//&err_code
	process_command_block(cmnd, &err_code, env);//returns last cmd executed
	/*start	
	pid_t	last_pid;
	pid_t	pid;
	t_pipe	fds;
	int	j;

	j = 0;

	while (cmnd)
	{
		if (cmnd->connection_type == PIPE)
			safe_pipe(&fds);
		pid = safe_fork();
		if (pid == 0)
			process_child(cmnd, &fds, env_arr, j);
		last_pid = pid;
		if (cmnd->connection_type == PIPE || is_last_cmd_in_pipe(cmnd, j))
			update_pipes(&fds, j, cmnd->next);
		j++;
		if (cmnd->connection_type == AND || cmnd->connection_type == OR)
		{
			cmnd = cmnd->next;//return (cmnd);
			break ;
		}
		else
			cmnd = cmnd->next;
	}

	err_code = wait_for_status(last_pid, j);
	printf("Last cmd exited with status %d\n", err_code);
	free_split(env_arr);
	*///end
	return (err_code);
}

/* Sets a possible path for each command, or NULL if none is found */
static void	fill_cmd_paths(t_cmd *cmd, char *envpaths)
{
	t_cmd	*tmp_cmd;
	char	*path;

	tmp_cmd = cmd;
	path = NULL;
	while (tmp_cmd)
	{
		if (tmp_cmd->cmd)
			path = get_cmd_path(tmp_cmd->cmd[0], envpaths);
		tmp_cmd->path = path;
		path = NULL;
		if (tmp_cmd->subcommand)
			fill_cmd_paths(tmp_cmd->subcommand, envpaths);
		tmp_cmd = tmp_cmd->next;
	}
}
