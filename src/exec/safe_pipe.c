/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:21:04 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 11:22:33 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Protects the pipe command. In case of failure, prints the relevant 
 * error to STDERR and exits */
void	safe_pipe(t_pipe *fds)
{
	if (pipe(fds->next) == -1)
	{
		perror("minishell: pipe");
		exit(1);
	}
}
