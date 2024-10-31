/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/30 17:56:49 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		has_pipe(t_cmd *cmd);
static int		runs_in_pipes(t_cmd *command);
static t_cmd	*run_builtin(t_cmd *cmd, int *exit_status, t_env **env);
static int		op_condition_true(t_token_type operator, int status);

/*void	test_print(t_cmd *cmd)//
{
	printf("p:%p\n",cmd->cmd);
	printf("p_:%p\n",cmd->subcommand);
	printf("f:%p\n",cmd->files);
	if (cmd->cmd)
	{
		printf("p:%p\n",cmd->cmd[0]);
		if (cmd->cmd[0])
			printf("p:%p\n",cmd->cmd[1]);
	}
	if (!cmd->cmd)
	{
		if (cmd->subcommand)
		{
			printf("p_:%p\n",cmd->subcommand->cmd);
			if (cmd->subcommand->cmd)
				printf("p_:%p\n",cmd->subcommand->cmd[0]);
		}
	}
	if (cmd->files)
	{
		if (cmd->files->name)
			printf("fn:%s\n",cmd->files->name);
		printf("ft:%d\n",cmd->files->type);
		if (cmd->files->next)
			if (cmd->files->next->name)
			{
				printf("fn2:%p\n",cmd->files->next->name);
				printf("ft2:%d\n",cmd->files->next->type);
			}
	}
}*/

/* This function takes a series of commands and decides which to execute,
 * depending on the connections between them */
int	ft_analyze_cmd(t_env **env, t_cmd *current)
{
	int		err_code;

	//if (!current)//
		//test_print(current);//
	err_code = 0;
	while (current)
	{
		if (current->cmd)
		{
			if (has_pipe(current) || runs_in_pipes(current))
				current = process_command_block(current, &err_code, *env);
			else
			{
				if (current->files || current->connection_type == PIPE)
				{
					err_code = ft_analyze_cmd(env, current->next);//lo saltamos
					current = NULL;
				}
				else
					current = run_builtin(current, &err_code, env);
			}
		}
		else if (current->subcommand)
			err_code = ft_analyze_cmd(env, current->subcommand);
		else//files, heredocs
			current = process_command_block(current, &err_code, *env);
		if (current && op_condition_true(current->connection_type, err_code))
			current = current->next;
		else
			return (err_code);
	}
	return (err_code);
}

static int	has_pipe(t_cmd *cmd)
{
	if (cmd->connection_type == PIPE)
		return (1);
	else
		return (0);
}

static int	op_condition_true(t_token_type operator, int status)
{
	if (operator == AND && status == 0)
		return (1);
	if (operator == OR && status != 0)
		return (1);
	return (0);
}

	//##COMMANDS##//
	//SUBCOMMANDS
	//1)if cmd->cmd == NULL, but subC != NULL, run subC as block
	//BUILTINS (PIPELESS)
	//1)if connection_type == PIPE, update to next cmd.
	//2)if connection_type == AND / OR, we run builtin as block.
	
	//##LINKS##//
	//AND 
	//1)run block. 
	//2)if err_code != 0, stop. else, update to next cmd and go to 1) 
	//OR
	//1)run block.
	//2)if err_code == 0, stop. else, update to next cmd and go to 1) 

/* This function filters those builtins that cannot run through a PIPE */
static int	runs_in_pipes(t_cmd *command)//igual tiene truco y la podemos ignorar.
{
	char	*cmd_name;
	char	*cmd_arg;

	cmd_name = command->cmd[0];
	cmd_arg = command->cmd[1];
	if (!ft_strcmp(cmd_name, "exit"))
		if (command->connection_type != PIPE)
			return (0);
	if (!ft_strcmp(cmd_name, "unset"))//Aunque entre, no tiene efecto
		return (0);
	if (!ft_strcmp(cmd_name, "export"))////OJO! export sin cmnd[1] sí puede PIPE!!!
		if (cmd_arg)
			return (0);
	if (!ft_strcmp(cmd_name, "cd"))
		return (0);
	return (1);
}

/* This function runs a builtin depending on input, then returns the 
 * appropriate exit status */
static t_cmd	*run_builtin(t_cmd *cmd, int *exit_status, t_env **env)
{
	//unset, export, cd. Any builtins that do NOT work with pipes
	if (!ft_strcmp(cmd->cmd[0], "unset"))//ojo que esto es segfault si te pongo "unset"
		*exit_status = ft_unset(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))//sólo si NO tiene pipe
		*exit_status = ft_exit(cmd, 1);
	else if (!ft_strcmp(cmd->cmd[0], "export"))//sólo si tiene args
		*exit_status = ft_export(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))//sólo si NO tiene pipe
		*exit_status = ft_cd(cmd, *env);
	return (cmd);
}
