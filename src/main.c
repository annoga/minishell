/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:55:21 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 15:46:46 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>

int	debug = 2;//TEST, DELETE
int	g_mode;

/*Just for testing*/
char	*print_type(t_token_type type)
{
	if (type == 0)
		return ("NO_TYPE");
	else if(type == 1)
		return ("AND");
	else if(type == 2)
		return ("OR");
	else if(type == 3)
		return ("PIPE");
	else if(type == 4)
		return ("L_PAREN");
	else if(type == 5)
		return ("R_PAREN");
	else if(type == 6)
		return ("REDIR_IN");
	else if(type == 7)
		return ("REDIR_OUT");
	else if(type == 8)
		return ("APPEND");
	else if(type == 9)
		return ("HEREDOC");
	else if(type == 10)
		return ("COMMAND");
	else if(type == 11)
		return ("ARG");
	else if(type == 12)
		return ("SPACE_TOKEN");
	else if(type == 13)
		return ("SINGLE_QUOTE");
	else if(type == 14)
		return ("DOUBLE_QUOTE");
	else if(type == 15)
		return ("FILES");
	else if(type == 16)
		return ("EXIT_STATUS");
	else if(type == 17)
		return ("ENV");
	return ("UNDEFINED TYPE");
}

/*
static void	print_env(char **envp)
{	
	int	i;

	i = 0;
	printf("memes\n");
	if (envp)
	{
		while (envp[i])
			ft_putendl_fd(envp[i++], 1);
	}
	printf("memes\n\n\n\n");
}
*/

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_env	*env;
	t_signal	signals;

	(void)argc;
	(void)argv;
	env = NULL;
	
	g_mode = 0;
	ft_catch_env(envp, &env);
	env->exit_status = 0;
	handle_update_signal(&signals, SIG_HANDLE_IDLE);
	while (1)
	{
		line = readline("💩 nugget 🐾$ ");
		//env->exit_status = 0;
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
