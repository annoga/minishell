#include "../../inc/minishell.h"

static void	set_command(t_cmd **cmd, t_token *token)
{
	char	*tmp;

	if (!(*cmd))
		*cmd = add_command(cmd);
	if (!(*cmd))
		return (lstclear(cmd, del_command));
	tmp = ft_strdup(token->token);
	if (!tmp)
		return (lstclear(cmd, del_command));
	(*cmd)->cmd = add_dir((*cmd)->cmd, tmp);
	if (!(*cmd)->cmd)
		return (lstclear(cmd, del_command), free(tmp));
}

static void	set_connection(t_token *token, t_cmd **command)
{
	t_cmd	*new_cmd;

	if (*command)
		(*command)->connection_type = token->syntaxis;
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		return (lstclear(command, del_command));
	(*command)->next = new_cmd;
	*command = new_cmd;
}

void ft_join_last(t_cmd *cmd, t_token *token, t_token_type last_type)
{
	char *join;
	t_file *aux;
	int i;
	
	i = 0;
	aux = cmd->files;
	printf("hola Mundo\n");
	printf("last_type: %s\n", print_type(last_type));
	if((last_type == ARG || last_type == COMMAND) && cmd->cmd && cmd->cmd[0])
	{
		while(cmd->cmd[i + 1])
			i++;
		join = ft_strjoin(cmd->cmd[i], token->token);
		free(cmd->cmd[i]);
		cmd->cmd[i] = join;
	}
	else if (last_type >= REDIR_IN && last_type <= HEREDOC)
	{
		printf("Hola file\n");
		while(aux && aux->next)
			aux = aux->next;
		join = ft_strjoin(aux->name, token->token);
		free(aux->name);
		if(token->type == DOUBLE_QUOTE || token->type == SINGLE_QUOTE)
			aux->is_quoted = 1;
		aux->name = join;
	}
}

static t_cmd *parser_two(t_token *token, t_cmd *command, t_cmd *head)
{
	t_token	*last_tkn;

	last_tkn = NULL;
    while (token)
    {
        if (!command)  // If no command exists yet, create the first command node
        {
            command = add_command(&command);
            head = command;  // Store the head of the list
        }
		if(last_tkn)
			printf("last_tkn: %p, token->type: %s, last_tkn->syntaxis: %s\n", last_tkn, print_type(token->type), print_type(last_tkn->syntaxis));
		else
			printf("last_tkn: %p, token->type: %s, last_tkn->syntaxis: %s\n", last_tkn, print_type(token->type), print_type(0));
		if(last_tkn && token->type != SPACE_TOKEN  && (token->type == ARG || token->type == DOUBLE_QUOTE || token->type == SINGLE_QUOTE) &&
			(last_tkn->syntaxis == COMMAND || last_tkn->syntaxis == ARG || (last_tkn->syntaxis >= REDIR_IN && last_tkn->syntaxis <= HEREDOC)))
			ft_join_last(command, token, last_tkn->syntaxis);
        else if (token->syntaxis == COMMAND || token->syntaxis == ARG)
            set_command(&command, token);
        else if (token->syntaxis == AND || token->syntaxis == OR || token->syntaxis == PIPE)
            set_connection(token, &command);
        else if (token->syntaxis >= REDIR_IN && token->syntaxis <= HEREDOC)
		{
		last_tkn = token;
		printf("last tkn type: %s\n", print_type(last_tkn->syntaxis));
            set_file(&command, &token);
			continue ;
		}
        else if (token->syntaxis == L_PAREN)
		{
            set_subcommand(&command, &token);
			continue ;
		}
		else if (token->syntaxis == R_PAREN)
			return (head);
		printf("##last token dir: %p\n", last_tkn);
		last_tkn = token;
		printf("#last token dir: %p\n", last_tkn);
        if (token)
            token = token->next;
    }
    return (head);
}

t_cmd *parser(t_token *token)
{
    t_cmd *command;
    t_cmd *head;  // Keep track of the head of the command list

	command = NULL;
    head = NULL;
	return parser_two(token, command, head);
}

// (echo "1" && (echo "2" && echo "3")) || echo "4" 
// (echo "hello" && echo "world") || (echo "goodbye" && echo "world")
//     printf("NO_TYPE = 0, AND = 1, OR = 2, PIPE = 3, L_PAREN = 4, R_PAREN = 5, REDIR_IN = 6, REDIR_OUT = 7, HEREDOC = 8, APPEND = 9, COMMAND = 10,\nARG = 11, SPACE_TOKEN = 12, SINGLE_QUOTE = 13, DOUBLE_QUOTE = 14, FILES = 15, EXIT_STATUS = 16, ENV = 17\n");
