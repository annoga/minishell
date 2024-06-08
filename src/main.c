/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:55:21 by angeln            #+#    #+#             */
/*   Updated: 2024/05/23 20:16:53 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>

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
		printf("Token: '%s', type: %u\n", tmp->token, tmp->type);
		tmp = tmp->next;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_token	*token;
	t_env	*head;
	int		i;

	(void)argc;
	(void)argv;
	// (void)envp;
	head = NULL;
	token = NULL;
	i = 1;

	ft_catch_env(envp, &head);
	while (i)
	{
		line = readline("💩 nugget 🐾$ ");
		printf("line: %s\n", line);
		if (ft_strncmp(line, "exit") == 0)
		{
			free(line);
			return (0);
		}
		if (line[0] != '\0')
		{
			token = split_linker(line);
			if(!token)
				return(1);
			add_history(line);
		}
		free(line);
		free_token(token);
		rl_on_new_line();
	}
	exit(0);
	return (0);
}
