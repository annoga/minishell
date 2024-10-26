/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:21:09 by angeln            #+#    #+#             */
/*   Updated: 2024/10/26 16:27:03 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pipes(t_pipe *fds, int j)
{
	close(fds->prev[READ]);
	close(fds->prev[WRITE]);
	//en todos menos el último y el primero
	fds->prev[READ] = fds->next[READ];
	fds->prev[WRITE] = fds->next[WRITE];
	if (j == 0)//
		j++;//
}
