#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_token_type
{
	NO_TYPE = 0,
	AND,
	OR,
	PIPE,
	L_PAREN,
	R_PAREN,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	COMMAND,
	ARG,
	SPACE_TOKEN,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	FILES,
	EXIT_STATUS,
	ENV
}					t_token_type;

typedef enum e_pipe_ends
{
	READ = 0,
	WRITE = 1
}					t_pipe_ends;

typedef struct s_pipe
{
	int	prev[2];
	int	next[2];
}					t_pipe;

typedef struct s_token
{
	char			*token;
	int				is_quote;
	t_token_type	type;
	t_token_type	syntaxis;
	struct s_token	*next;
}					t_token;

typedef struct s_file
{
	char			*name;
	t_token_type	type;
	struct s_file	*next;
}					t_file;

typedef struct s_env
{
	char			*key_name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_wilds
{
    const char *path;
    const char *prefix;
    const char *suffix;
    int depth;
}	t_wilds;


typedef struct s_synt
{
	t_token_type	last_token_type;
	int				parenthesis_balance;
	int				is_cmd_assigned;
	int				expecting_cmd;
	int				has_content;
}	t_synt;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	t_file			*files;
	t_token_type	connection_type; //AND, OR, PIPE
	int 			parenthesis;
	struct s_cmd	*subcommand;
	struct s_cmd	*next;
}	t_cmd;

#endif
