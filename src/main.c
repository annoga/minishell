/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:55:21 by angeln            #+#    #+#             */
/*   Updated: 2024/09/24 17:59:18 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>

int	debug = 1;//TEST, DELETE

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
		return ("HEREDOC");
	else if(type == 9)
		return ("APPEND");
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

/*Just for testing*/
void	print_list(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	printf("----------------------\n");
	while (tmp)
	{
		// printf("Token: '%s', type: %u\n", tmp->token, tmp->type);
		printf("%s", tmp->token);
		tmp = tmp->next;
	}
	printf("\n");
	tmp = head;
	printf("----------------------\n");
	while (tmp)
	{
		printf("Token: '%s', type: %s\n", tmp->token, print_type(tmp->syntaxis));
		tmp = tmp->next;
	}
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
