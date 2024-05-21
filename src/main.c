/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: anovoa <anovoa@student.42barcelon>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/16 11:55:21 by angeln			   #+#	  #+#			  */
/*	 Updated: 2024/05/21 21:14:03 by anovoa			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

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
			add_history(line);
		}
		rl_on_new_line();
	}
	return (0);
}
