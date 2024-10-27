/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:03:18 by angeln            #+#    #+#             */
/*   Updated: 2024/10/17 14:07:05 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* This function returns 1 if the given path can be executed, 0 otherwise. */
int	is_command(char *path)
{
	if (access(path, X_OK) == 0)
		return 1;
	else
		return 0;
}
