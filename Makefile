# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 11:58:32 by angeln            #+#    #+#              #
#    Updated: 2024/05/21 20:56:37 by anovoa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#app name
NAME = minishell

#lib name
LFT = ftgnl

HEADER = minishell.h

#===================DIR===================#
#=========================================#

SRCDIR = src

OBJDIR = obj

#lib dir
LFTDIR = libft

#===================GCC===================#
#=========================================#
#compilation warnings
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

#Omit path to .h, can also use <libname.h>
#-I includedir 
INCFLAGS = -I$(LFTDIR) -Iinc
# Omit .a file
#-L libdir -l libname
LIBFLAGS = -Lreadline -lreadline -lhistory -ltermcap 

#==================FILES==================#
SRC = main.c 

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#==================RULES==================#
#=========================================#
all: $(NAME)


$(NAME): 
	cc $(CFLAGS) -Iinc $(LIBFLAGS) -DREADLINE_LIBRARY src/main.c -o $(NAME)

.PHONY: minishell
