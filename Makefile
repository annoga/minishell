#Program name
NAME				=	minishell

# Compiler and CFlags
CC					=	gcc -g
CFLAGS				=	-Wall -Werror -Wextra
#CFLAGS				=	-Wall -Werror -Wextra -fsanitize=address
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
SRC					=	main.c \


SRCS				=	$(addprefix $(SRC_DIR), $(SRC))

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
