/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_soft_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:22:29 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:22:32 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_soft_itoa(t_env **tmp, int n)
{
	(*tmp)->value = ft_itoa(n);
	if (!(*tmp)->value)
		return_error("MALLOC");
}
