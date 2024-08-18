#Program name
NAME				=	minishell

# Compiler and CFlags
CC					=	gcc -g
CFLAGS				=	-Wall -Werror -Wextra
# CFLAGS				=	-Wall -Werror -Wextra -fsanitize=address
RM					=	rm -f
# 
# Determine the platform
LIBS = -Lreadline -lreadline -lhistory -ltermcap
INC = inc/minishell.h libft/libft.h

# Apaños para mac
#LIBS = -Lreadline -lreadline -ltermcap

# Directories
LIBFT				=	./libft/libftgnl.a
SRC_DIR				=	src/
OBJ_DIR				=	obj/

# Source Files

HANDLE_TOKENS	=	handle_tokens/handle_args.c			\
					handle_tokens/handle_double_quote.c	\
					handle_tokens/handle_single_quote.c	\
					handle_tokens/handle_space.c			\
					handle_tokens/handle_dollar.c			\
					handle_tokens/handle_parenthesis.c	

TOKENIZER 		= 	tokenizer/tokenizer.c					\
					tokenizer/get_token.c					\
					tokenizer/get_special_token.c			\
					tokenizer/add_token.c					\
					tokenizer/create_token.c				\
					tokenizer/free_token.c				\
					tokenizer/new_token.c

UTILS			=	utils/ft_strncmp.c					\
					utils/ft_strndup.c					\
					utils/check_is_ok.c					\
					utils/ft_istoken.c					\
					utils/sort_alphabetic_order.c		\
					utils/return_error.c

PARSER			=	parser/expansor.c						\
					parser/prueba_env.c					\
					parser/ft_fnmatch.c					\
					parser/expansor_wildcard.c			\
					parser/match_wildcards_in_directory.c	\
					parser/wildcard_utils.c			\
					parser/push_midlist.c						

EXEC			=	exec/echo.c exec/mock_builtin_tokenizer.c \
					exec/ft_exit.c \
					exec/ft_env.c

MAIN			=	main.c								\
					split_linker.c

SRC				=	$(HANDLE_TOKENS) $(TOKENIZER) $(UTILS) $(PARSER) $(EXEC) $(MAIN)


SRCS			=	$(addprefix $(SRC_DIR), $(SRC))

# Object files
OBJ 				= 	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules

all: 					makelib $(NAME)


$(NAME): 				$(OBJ) $(LIBFT)
						@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
						@echo "\033[1;32mAll minishell done!!✅\033[1;97m"
						


makelib:
						@make -C ./libft

# Compile object files from source files
$(OBJ_DIR)%.o:			$(SRC_DIR)%.c Makefile $(INC)
						@mkdir -p $(@D)
						@$(CC) $(CFLAGS) -c $< -o $@
						@echo "\033[1;31mCompiling...\033[1;97m	"$< "✅"

clean:
						@$(RM) -r $(OBJ_DIR)
						@make clean -C ./libft
						@echo "\033[1;32mAll cleaned 💩🗑\033[1;97m"

fclean: 				clean
						@$(RM) $(NAME)
						@$(RM) $(LIBFT)

re: 					fclean all

# Phony targets represent actions not files
.PHONY: 				all clean fclean re makelib
