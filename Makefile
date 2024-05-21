# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 21:11:22 by anovoa            #+#    #+#              #
#    Updated: 2024/05/21 21:38:21 by anovoa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LIBFLAGS = -Lreadline -lreadline -lhistory -ltermcap

NAME = minishell
#==================FILES==================#
SRC = main.c

#==================RULES==================#
#=========================================#
all: $(NAME)

$(NAME):
	cc $(CFLAGS) -Iinc $(LIBFLAGS) -DREADLINE_LIBRARY src/main.c -o $(NAME)

.PHONY: minishell
