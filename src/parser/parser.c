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


static void	set_heredoc(t_cmd **cmd, t_token **token)
{
	if (!(*cmd))
		*cmd = add_command(cmd);
	if (!(*cmd))
		return (lstclear(cmd, del_command));
	while (*token && (*token)->syntaxis != FILES)
		*token = (*token)->next;
	if (!(*token))
		return (lstclear(cmd, del_command));
	(*cmd)->heredoc = (char **)add_dir((*cmd)->heredoc, (*token)->token);
	if (!(*cmd)->heredoc)
		return (lstclear(cmd, del_command));
	*token = (*token)->next;
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

static t_cmd *parser_two(t_token *token, t_cmd *command, t_cmd *head)
{
    while (token)
    {
        if (!command)  // If no command exists yet, create the first command node
        {
            command = add_command(&command);
            head = command;  // Store the head of the list
        }
        if (token->syntaxis == COMMAND || token->syntaxis == ARG)
            set_command(&command, token);
        else if (token->syntaxis == AND || token->syntaxis == OR || token->syntaxis == PIPE)
            set_connection(token, &command);  // Modify the function call to pass the command pointer by reference
        else if (token->syntaxis >= REDIR_IN && token->syntaxis <= APPEND)
            set_file(&command, &token);
        else if (token->syntaxis == HEREDOC)
            set_heredoc(&command, &token);
        else if (token->syntaxis == L_PAREN)
		{
            set_subcommand(&command, &token);
			continue ;
		}
		else if (token->syntaxis == R_PAREN)
			return (head);
        if (token)
            token = token->next;
    }
    return head;
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
