/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:55:21 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 23:17:17 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_mode;

static void	init_sys(int argc, char *argv[], t_env **env);

int	main(int argc, char *argv[], char **envp)
{
	char		*line;
	t_env		*env;
	t_signal	signals;

	init_sys(argc, argv, &env);
	ft_catch_env(envp, &env);
	env->exit_status = 0;
	handle_update_signal(&signals, SIG_HANDLE_IDLE);
	while (1)
	{
		line = readline("💩 nugget 🐾$ ");
		if (g_mode == 130)
			env->exit_status = 130;
		if (!line && ft_putendl_fd("exit", 2) && free_env(&env))
			exit(0);
		if (line && line[0] != '\0' && !check_is_ok(line, env))
		{
			split_linker(line, &env);
			add_history(line);
		}
		free(line);
		rl_on_new_line();
	}
	exit(0);
	return (0);
}

static void	init_sys(int argc, char *argv[], t_env **env)
{
	(void)argc;
	(void)argv;
	*env = NULL;
	g_mode = 0;
}
