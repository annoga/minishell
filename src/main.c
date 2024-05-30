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
		// printf("Token: '%s', type: %u\n", tmp->token, tmp->type);
		printf("%s", tmp->token);
		tmp = tmp->next;
	}
}

t_token *split_linker(char *line)
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
	return (token);
}

void free_token(t_token *token)
{
	t_token *tmp;

	while(token)
	{
		tmp = token;
		token = token->next;
		if(tmp->type == ARG)
		{
			free(tmp->token);

			free(tmp);
		}
	}
}

int	main(void)
{
	char	*line;
	t_token *token;

	token = NULL;
	int i = 1;
	while (i--)
	{
		line = readline("💩 nugget 🐾$ ");
		if (line[0] != '\0')
		{
			token = split_linker(line);
			add_history(line);
		}
		free_token(token);
		rl_on_new_line();
	}

	exit(0);
	return (0);
}
