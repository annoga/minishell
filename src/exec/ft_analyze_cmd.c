/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/30 01:50:46 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function takes a series of commands and decides which to execute,
 * depending on the connections between them */
int	ft_analyze_cmd(t_env *env, t_cmd *cmnd)
{
	int		err_code;

	//SUBCOMMANDS
	//1)if cmd->cmd == NULL, but subC != NULL, run subC as block
	//AND 
	//1)run block. 
	//2)if err_code != 0, stop. else, update to next cmd and go to 1) 
	//n)keep last err_code
	//OR
	//1)run block.
	//2)if err_code == 0, stop. else, update to next cmd and go to 1) 
	//BUILTINS (PIPELESS)
	//1)if connection_type == PIPE, update to next cmd.
	//2)if connection_type == AND / OR, we run builtin as block.
	process_command_block(cmnd, &err_code, env);//returns last cmd executed
	return (err_code);
}

