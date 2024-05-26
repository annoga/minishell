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

void split_modded(char *line, char c)
{
	int i;
	char **split;
	split = ft_split(line, c);
	t_token *head;

	i = 0;
	head = ft_lstnew(split[i]);
	i = 1;
	while(split[i])
	{
		head->next = ft_lstnew(split[i]);
		head = head->next;
		printf("split[%d]: %s\n", i, head->token);
		i++;
	}
}

int	main(void)
{
	char	*line;
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
			split_modded(line, ' ');
			add_history(line);
		}
		rl_on_new_line();
	}
	return (0);
}
