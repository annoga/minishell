# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 22:41:29 by anovoa            #+#    #+#              #
#    Updated: 2024/03/01 21:34:32 by anovoa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftgnl.a

HEADER = libft.h

OBJDIR = obj

SOURCES = ft_isalpha.c ft_toupper.c ft_isdigit.c ft_tolower.c \
      ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
      ft_atoi.c ft_strrchr.c ft_strdup.c ft_substr.c \
      ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
      ft_printf.c ft_printf_aux.c ft_solve_types_1.c ft_solve_types_2.c \
      ft_writers.c get_next_line.c get_next_line_utils.c \
	  get_whole_file.c ft_atoi_base.c ft_countdigits.c \
	  ft_isspace.c ft_issign.c ft_strnstr.c ft_strlcat.c

OBJECTS = $(SOURCES:.c=.o)

CC = gcc

CFLAGS = #-Wall -Wextra -Werror -g
#-fsanitize=address
#-g

all: $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@echo "linking $@"
	ar -rcs $@ $^

clean:
	@echo "deleting libftgnl object files"
	@rm -f $(OBJECTS) 

fclean: clean
	@echo "deleting $(NAME)"
	@rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
