/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:35:28 by crmanzan          #+#    #+#             */
/*   Updated: 2024/10/28 17:35:39 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*handle_space(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	(*i)--;
	return (create_token(SPACE_TOKEN, " ", i));
}
