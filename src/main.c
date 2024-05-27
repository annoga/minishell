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
//#include <readline/readline.h>
//#include <readline/history.h>

void print_list(t_token *head)
{
	t_token *tmp;
	tmp = head;
	printf("----------------------\n");
	while(tmp)
	{
    	printf("token: %s, is_builtin: %d, is_pipe: %d, is_redir: %d, is_arg: %d, is_bonus: %d\n", tmp->token, tmp->is_builtin, tmp->is_pipe, tmp->is_redir, tmp->is_arg, tmp->is_bonus);
		tmp = tmp->next;
	}
}

void split_linker(char *line)
{
	int i;
	char **split;
	split = split_line(line, skip_separator, skip_to_next_word);
	t_token *head;
	t_token *tmp;

	i = 0;
	head = ft_lstnew(split[i]);
	tmp = head;
	i = 1;
	while(split[i])
	{
		tmp->next = ft_lstnew(split[i]);
		tmp = tmp->next;
		i++;
	}
	
	print_list(head);
	

	printf("\n");
}

int	main(void)
{
	char	*line;
	// int i = 3;
	while (1)
	{
		line = readline("💩 nugget 🐾$ ");

		

			
/*		if(line[0] == 'd' && line[1] == '\0')
		{
			printf("you deleted the history\n");
			rl_clear_history();
		}
*/		if (line[0] != '\0')
		{
			split_linker(line);
			
			add_history(line);
		}
		rl_on_new_line();
	}
	exit(0);
	return (0);
}
