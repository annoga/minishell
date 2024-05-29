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

void print_list(t_token *head)
{
	t_token *tmp;
	tmp = head;
	printf("----------------------\n");
	while(tmp)
	{
		printf("Token: %s, type: %u\n", tmp->token, tmp->type);
		tmp = tmp->next;
	}
}

void split_linker(char *line)
{
	// int i;
	t_token *token;
	// char **split;
	token = new_split(line);
	// t_token *head;
	// t_token *tmp;

	// i = 0;
	// head = ft_lstnew(split[i]);
	// tmp = head;
	// i = 1;
	// while(split[i])
	// {
	// 	tmp->next = ft_lstnew(split[i]);
	// 	tmp = tmp->next;
	// 	i++;
	// }
	print_list(token);
	printf("\n");
}

int	main(void)
{
	char	*line;
	// int i = 3;
	while (1)
	{
		line = readline("💩 nugget 🐾$ ");
		if (line[0] != '\0')
		{
			split_linker(line);
			add_history(line);
		}
		rl_on_new_line();
	}
	exit(0);
	return (0);
}
