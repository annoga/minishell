/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 handle_exit_status.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/04 12:39:12 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/04 12:39:12 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*parse_exit_status(int *i)
{
	t_token	*token;

	(*i) += 1;
	token = new_token(EXIT_STATUS, ft_strdup("$?"));
	return (token);
}
