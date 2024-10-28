/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/28 19:29:19 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	fill_cmd_paths(t_cmd *cmd, char *envpaths);

/* This function takes one or more commands and goes through them */
int	ft_analyze_cmd(t_env *env, t_cmd *cmnd)
{
//	char	*path;
	char	**env_arr;
	// t_cmd	*cmnd;
//	int		i;//
//	i = 0;//
	env_arr = ft_get_env_array(env);//need to free_split when done
	if (!env_arr)
	{
		printf("error translating t_env\n");
		return (0);
	}
//	while (env_arr[i])//
//		printf("%s\n", env_arr[i++]);//print envp

	fill_cmd_paths(cmnd, ft_getenv("PATH", env));

//	printf("cmd[0]:%s\n", cmnd->cmd[0]);
//	printf("cmd[1]:%s\n", cmnd->cmd[1]);
	t_cmd	*tmp2;

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
	}

	int		err_code;
	pid_t	last_pid;
	pid_t	pid;
	t_pipe	fds;
	int	j;

	j = 0;
	pid_t	pid_arr[MAX_CMD];//

	ft_bzero(pid_arr, sizeof(pid_arr));//
	while (cmnd)
	{
	//	printf("path:%s\n", cmnd->path);
		if (cmnd->connection_type == PIPE)
		{
			if (pipe(fds.next) == -1)//msg if err?
				printf("pipe error. Oh shit!\n");
//		printf("dad#%i - read:%i, write:%i\n",j,fds.next[READ],fds.next[WRITE]);
		}
		pid = do_fork();
		if (pid == 0)
		{
			process_child(cmnd, &fds, env_arr, j);
		}
		pid_arr[j] = pid;
		last_pid = pid;
		//en todas las secuencias en las que ha habido al menos un PIPE
		if (cmnd->connection_type == PIPE || (j != 0 && !cmnd->next))
			update_pipes(&fds, j, cmnd->next);
	//free path

		//Volcamos el resultado de la pipe
/*		if (cmnd->connection_type == PIPE || (j != 0 && !cmnd->next))
		{
			printf("here j:%i\n", j);
			close(fds.next[WRITE]);
		}
*/		cmnd = cmnd->next;
		j++;
	}

//	if (j >= 0)//
//		j++;//

	int	stat_loc;
	int	k;

	k = 0;

	while (k++ < j)
	{
		pid = waitpid(-1, &stat_loc, 0);
		if (pid == last_pid)
		{
				err_code = stat_loc;
			//if (WIFEXITED(stat_loc))
				//err_code = WEXITSTATUS(stat_loc);// Faltaría signal check
		}
	}
	if (WIFEXITED(err_code))
	{
		printf("Last cmd exited with status %d\n", WEXITSTATUS(err_code));
		err_code = WEXITSTATUS(err_code);
	}
	free_split(env_arr);
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
		//printf("path:%s\n", path);
		tmp_cmd->path = path;
		path = NULL;
		if (tmp_cmd->subcommand)
			fill_cmd_paths(tmp_cmd->subcommand, envpaths);
		tmp_cmd = tmp_cmd->next;
	}
}
