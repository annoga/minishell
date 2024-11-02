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
INC = inc/minishell.h inc/struct.h libft/libft.h

# Apaños para mac
#LIBS = -Lreadline -lreadline -ltermcap

# Directories
LIBFT				=	./libft/libftgnl.a
SRC_DIR				=	src/
OBJ_DIR				=	obj/

# Source Files

HANDLE_TOKENS	=	handle_tokens/handle_args.c				\
					handle_tokens/handle_double_quote.c		\
					handle_tokens/handle_single_quote.c		\
					handle_tokens/handle_space.c			\
					handle_tokens/handle_expansion.c		\
					handle_tokens/handle_parenthesis.c	

TOKENIZER 		= 	tokenizer/tokenizer.c					\
					tokenizer/get_token.c					\
					tokenizer/get_special_token.c			\
					tokenizer/add_token.c					\
					tokenizer/create_token.c				\
					tokenizer/free_token.c					\
					tokenizer/new_token.c

UTILS			=	utils/ft_strcmp.c						\
					utils/ft_strndup.c						\
					utils/ft_strncmp.c						\
					utils/ft_strstr.c						\
					utils/ft_strncpy.c						\
					utils/check_is_ok.c						\
					utils/ft_istoken.c						\
					utils/sort_alphabetic_order.c			\
					utils/ft_soft_itoa.c					\
					utils/lst_add_back.c					\
					utils/lstclear.c						\
					utils/free_split.c						\
					utils/free_tcmd.c						\
					utils/ft_memmove.c						\
					utils/return_error.c
 
PARSER			=	parser/parser.c							\
					parser/add_dir.c						\
					parser/add_command.c					\
					parser/del_command.c					\
					parser/set_subcommand.c					\
					parser/set_file.c						

ENV				=	env/ft_catch_env.c						\
					env/ft_empty_env.c						\
					env/ft_getenv.c

SYNTAX			=	syntax/analize_syntax.c					\
					syntax/assign_type.c					

EXPANSOR		=	expansor/expansor_wildcard.c			\
					expansor/expansor.c						\
					expansor/expansor_hdoc.c				\
					expansor/last_slash.c					\
					expansor/insert_space_tokens.c			\
					expansor/list_all_directories.c			\
					expansor/process_entry.c				\
					expansor/push_midlist.c					\
					expansor/wildcard_utils.c						

EXEC			=	exec/free_env.c 							\
					exec/command_analyzer.c						\
					exec/ft_analyze_cmd.c						\
					exec/get_heredocs.c							\
					exec/is_command.c							\
					exec/get_cmd_path.c							\
					exec/tenv_to_array.c						\
					exec/pipe_write_stdout.c					\
					exec/pipe_read_stdin.c						\
					exec/is_last_cmd_in_pipe.c					\
					exec/update_pipes.c							\
					exec/clear_heredoc.c						\
					exec/process_command_block.c				\
					exec/process_child.c						\
					exec/redir_file_stdout.c					\
					exec/redir_file_stdin.c						\
					exec/redir_heredoc_stdin.c					\
					exec/safe_fork.c								

BUILTINS			=	builtins/echo.c 								\
					builtins/ft_exit.c 								\
					builtins/ft_env.c 								\
					builtins/ft_pwd.c 								\
					builtins/ft_cd.c 							\
					builtins/ft_unset.c 							\
					builtins/export_utils.c 							\
					builtins/ft_export.c 							
					

SIGNAL				=	signal/handle_update_signal.c

MAIN			=	main.c									\
					split_linker.c							\
					print_functions.c

SRC				=	$(HANDLE_TOKENS) $(TOKENIZER) $(UTILS) $(PARSER) $(ENV) $(SYNTAX) $(EXEC) $(EXPANSOR) $(MAIN) $(SIGNAL) $(BUILTINS)


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
