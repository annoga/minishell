/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/30 09:34:36 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		can_pipe(t_cmd *command);
static t_cmd	*run_builtin(t_cmd *cmd, int *exit_status, t_env **env);

static void	test_print(t_cmd *cmd)//
{
	printf("p:%p\n",cmd->cmd);
	printf("p_:%p\n",cmd->subcommand);
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
}

/* This function takes a series of commands and decides which to execute,
 * depending on the connections between them */
int	ft_analyze_cmd(t_env **env, t_cmd *cmd)
{
	int		err_code;
	t_cmd	*current;

	if (!cmd)
		test_print(cmd);//
	current = cmd;
	while (current)
	{
		if (current->cmd)
		{
			if (!can_pipe(current))
			{
				if (current->files || current->connection_type == PIPE)
				{
					err_code = ft_analyze_cmd(env, current->next);//lo saltamos
					current = NULL;
				}
				else
					current = run_builtin(current, &err_code, env);
			}
			else
				current = process_command_block(current, &err_code, *env);
		}
		else if (current->subcommand)//files o subC
		{
			err_code = ft_analyze_cmd(env, current->subcommand);
			//restart loop. Según err_code, evalúas si AND/OR se ejecuta
		}
		else//files, heredocs
			current = process_command_block(current, &err_code, *env);
		if (current && current->connection_type == AND && err_code == 0)
			current = current->next;
		else if (current && current->connection_type == OR && err_code != 0)
			current = current->next;
		else
			return (err_code);
	}
	return (err_code);
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
	//n)keep last err_code
	//OR
	//1)run block.
	//2)if err_code == 0, stop. else, update to next cmd and go to 1) 
	//process_command_block(cmd, &err_code, env);//returns last cmd executed

/* This function filters those builtins that cannot run through a PIPE */
static int	can_pipe(t_cmd *command)
{
	char	*cmd_name;
	char	*cmd_arg;

	cmd_name = command->cmd[0];
	cmd_arg = command->cmd[1];
	if (!ft_strcmp(cmd_name, "exit"))
		if (command->connection_type != PIPE)
			return (0);
	if (!ft_strcmp(cmd_name, "unset"))//hace algo sin args?
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
	//unset, export. Any builtins that do NOT work with pipes
	if (!ft_strcmp(cmd->cmd[0], "unset"))//ojo que esto es segfault si te pongo "unset"
		*exit_status = ft_unset(cmd->cmd[1], env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))//sólo si NO tiene pipe
		*exit_status = ft_exit(cmd);
	//else if (!ft_strcmp(cmd->cmd[0], "export"))
		//*exit_status = ft_export(cmd->cmd, env);
	return (cmd);
}
