/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/27 21:10:28 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function takes one or more commands and goes through them */
int	ft_analyze_cmd(t_env *env, t_cmd *cmnd)
{
	char	*path;
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
	// cmnd = parser(head);//tb debe liberarse
	//Calculo path para cada comando. Por ahora ignoro subcmds
	t_cmd	*tmp_cmd;

	tmp_cmd = cmnd;
	while (tmp_cmd)
	{
//	path = find_cmd_path(cmnd->cmd[0], ft_getenv("PATH", env));
	path = get_cmd_path(tmp_cmd->cmd[0], ft_getenv("PATH", env));
	printf("path:%s\n", path);
//	if (path == NULL)
//		return (0);
	tmp_cmd->path = path;
	tmp_cmd = tmp_cmd->next;
	}

//	return (0);	
/*	printf("cmd[0]:%s\n", cmnd->cmd[0]);
	printf("cmd[1]:%s\n", cmnd->cmd[1]);
	printf("path:%s\n", cmnd->path);
	printf("next:%p\n", cmnd->next);//NULL if empty
	if (cmnd->files)
	{
	printf("conType:%i\n", cmnd->connection_type);//NULL if empty
	printf("fName:%s\n", cmnd->files->name);//
	printf("fType:%i\n", cmnd->files->type);//
	printf("fNxt:%p\n", cmnd->files->next);//
	}
*/
	//if cmd exists
//	path[0] = '\n';
	int		err_code;
	pid_t	last_pid;
	pid_t	pid;
	t_pipe	fds;
	int	j;

	j = 0;
	pid_t	pid_arr[MAX_CMD];

	ft_bzero(pid_arr, sizeof(pid_arr));
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
			exec_child(cmnd, &fds, env_arr, j);
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
		//printf("----Command Finished----\n");
		//printf("Last cmd exited with status %d\n", WEXITSTATUS(err_code));
		err_code = WEXITSTATUS(err_code);
		//printf("err_code: %d\n", err_code);
	}
//	printf("pid:%i\nlast_pid:%i\nerr_code:%i\n", pid, last_pid, err_code);
	return (err_code);
}
