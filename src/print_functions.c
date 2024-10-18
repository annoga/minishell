#include "../inc/minishell.h"


void	print_list(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	printf("----------------------\n");
	while (tmp)
	{
		// printf("Token: '%s', type: %u\n", tmp->token, tmp->type);
		printf("%s", tmp->token);
		tmp = tmp->next;
	}
	printf("\n");
	tmp = head;
	printf("----------------------\n");
	while (tmp)
	{
		printf("Token: '%s', type: %s\n", tmp->token, print_type(tmp->syntaxis));
		tmp = tmp->next;
	}
}

// Helper function to print the redirection type
const char *get_redirection_type(t_token_type type) {
    switch (type) {
        case REDIR_IN:  return "<";
        case REDIR_OUT: return ">";
        case APPEND:    return ">>";
        case HEREDOC:   return "<<";
        default:        return "?";
    }
}

// Helper function to print connection type (AND, OR, PIPE)
const char *get_connection_type(t_token_type type) {
    switch (type) {
        case AND:  return "&&";
        case OR:   return "||";
        case PIPE: return "|";
        default:   return "?";
    }
}

void print_cmd(t_cmd *cmd, int level)
{
    if (!cmd) {
        printf("No commands\n");
        return;
    }

    while (cmd) {
        // printf("%*sI'm in this commando: %p\n",level * 4,"", cmd);
        // Print each command and its arguments on a single line
        if (cmd->cmd) {
            printf("%*sCommand: ", level * 4, "");  // Indentation based on level
            for (int i = 0; cmd->cmd[i]; i++) {
                printf("%s ", cmd->cmd[i]);
            }
            printf("\n");
        }

        // Print file redirections with indentation
        if (cmd->files) {
            printf("%*sRedirections:\n", level * 4, "");
            t_file *file = cmd->files;
            while (file) {
                printf("%*s  %s %s\n", level * 4, "", get_redirection_type(file->type), file->name);
                file = file->next;
            }
        }

        // Print subcommands with increased indentation level
        if (cmd->subcommand) {
            printf("%*sSubcommand:\n", level * 4, "");
            print_cmd(cmd->subcommand, level + 1);  // Recursive call with increased level
        }

        // Print connection type with indentation
        if (cmd->connection_type == AND || cmd->connection_type == OR || cmd->connection_type == PIPE) {
            printf("%*sConnection: %s\n", level * 4, "", get_connection_type(cmd->connection_type));
        }

        // Move to the next command in the sequence
        cmd = cmd->next;
    }
}