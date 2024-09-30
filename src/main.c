/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:55:21 by angeln            #+#    #+#             */
/*   Updated: 2024/08/19 20:39:30 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>

int	debug = 0;//TEST, DELETE




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
	t_token	*token;
	t_env	*env;
	t_cmd	*cmd;
	int		i;

	(void)argc;
	(void)argv;
	env = NULL;
	token = NULL;
	i = 1;
	ft_catch_env(envp, &env);
	while (i)
	{
		line = readline("💩 nugget 🐾$ ");
		//Ctrl+D: envia un NULL a readline -> salimos
		if (!line && ft_putendl_fd("exit", 2) && free_env(&env))
			exit(0);
		if (line && line[0] != '\0' && check_is_ok(line))
		{
			token = split_linker(line, &env);
			if(!token)
				continue;
			cmd = parser(token);
			// (void)cmd;
			if(debug == 2)
				print_cmd(cmd, 0);
			add_history(line);
		}
		free(line);
		free_token(&token);
		rl_on_new_line();
	}
	exit(0);
	return (0);
}
