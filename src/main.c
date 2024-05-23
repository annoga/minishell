/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:55:21 by angeln            #+#    #+#             */
/*   Updated: 2024/05/23 19:35:47 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//#include <readline/readline.h>
//#include <readline/history.h>



int	main(void)
{
	char	*line;
	char **split;

	int i = 0;
	while (1)
	{
		line = readline("💩 nugget 🐾$ ");
		split = ft_split(line, ' ');
		i = 0;
		while(split[i])
		{
			printf("%d. split: %s\n", i, split[i]);
			i++;
		}


/*		if(line[0] == 'd' && line[1] == '\0')
		{
			printf("you deleted the history\n");
			rl_clear_history();
		}
*/		if (line[0] != '\0')
		{
			add_history(line);
		}
		rl_on_new_line();
	}
	return (0);
}
