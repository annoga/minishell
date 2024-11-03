/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:07:57 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 10:52:56 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	clear_heredoc(t_file *target)
{
	//char	*filename;
	//char	*id;

	if (target->heredoc_fd == -1)
		return (0);
	if (safe_close(target->heredoc_fd) == -1)
		return (1);
	//id = ft_itoa(target->heredoc_fd);
	//filename = ft_strjoin("/tmp/temp_heredoc_", id);
	//free(id);
	target->heredoc_fd = -1;
	//unlink(filename);
	//free(filename);
	return (0);
}
