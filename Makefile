#Program name
NAME				=	minishell

# Compiler and CFlags
CC					=	gcc -g
# CFLAGS				=	-Wall -Werror -Wextra
CFLAGS				=	-Wall -Werror -Wextra -fsanitize=address
RM					=	rm -f
# 
# Determine the platform
LIBS = -Lreadline -lreadline -lhistory -ltermcap
INC = inc/minishell.h libft/libft.h

# Directories
LIBFT				=	./libft/libftgnl.a
SRC_DIR				=	src/
OBJ_DIR				=	obj/

# Source Files

HANDLE_TOKENS	=	$(SRC_DIR)handle_tokens/handle_args.c			\
					$(SRC_DIR)handle_tokens/handle_double_quote.c	\
					$(SRC_DIR)handle_tokens/handle_single_quote.c	\
					$(SRC_DIR)handle_tokens/handle_space.c			\
					$(SRC_DIR)handle_tokens/handle_dollar.c			\
					$(SRC_DIR)handle_tokens/handle_parenthesis.c	

TOKENIZER 		= 	$(SRC_DIR)tokenizer/tokenizer.c					\
					$(SRC_DIR)tokenizer/get_token.c					\
					$(SRC_DIR)tokenizer/get_special_token.c			\
					$(SRC_DIR)tokenizer/add_token.c					\
					$(SRC_DIR)tokenizer/create_token.c				\
					$(SRC_DIR)tokenizer/free_token.c				\
					$(SRC_DIR)tokenizer/new_token.c

UTILS			=	$(SRC_DIR)utils/ft_strncmp.c					\
					$(SRC_DIR)utils/ft_strndup.c					\
					$(SRC_DIR)utils/return_error.c

PARSER			=	$(SRC_DIR)parser/parser.c						

MAIN			=	$(SRC_DIR)main.c								\
					$(SRC_DIR)split_linker.c

SRC				=	$(HANDLE_TOKENS) $(TOKENIZER) $(UTILS) $(PARSER) $(MAIN)


# SRCS			=	$(addprefix $(SRC_DIR), $(SRC))

# Object files
OBJ 				= 	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

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
