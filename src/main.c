/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:55:21 by angeln            #+#    #+#             */
/*   Updated: 2024/08/19 20:39:30 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>

int	debug = 0;//TEST, DELETE

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
		printf("Token: '%s', type: %u\n", tmp->token, tmp->syntaxis);
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

// Function to print the parsed command structure
// Modified print function with indentation level
void print_cmd(t_cmd *cmd, int level) {
    if (!cmd) {
        printf("No commands\n");
        return;
    }

    while (cmd) {
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

        // Print heredocs with indentation
        if (cmd->heredoc) {
            for (int i = 0; cmd->heredoc[i]; i++) {
                printf("%*sheredoc[%d]: %s\n", level * 4, "", i, cmd->heredoc[i]);
            }
        } else {
            printf("%*sHeredoc array is NULL\n", level * 4, "");
        }

        // Print connection type with indentation
        if (cmd->connection_type == AND || cmd->connection_type == OR || cmd->connection_type == PIPE) {
            printf("%*sConnection: %s\n", level * 4, "", get_connection_type(cmd->connection_type));
        }

        // Print subcommands with increased indentation level
        if (cmd->subcommand) {
            printf("%*sSubcommand:\n", level * 4, "");
            print_cmd(cmd->subcommand, level + 1);  // Recursive call with increased level
        }

        // Move to the next command in the sequence
        cmd = cmd->next;
    }
}


/*
static void	print_env(char **envp)
{	
	int	i;

	i = 0;
	printf("memes\n");
	if (envp)
	{
		while (envp[i])
			ft_putendl_fd(envp[i++], 1);
	}
	printf("memes\n\n\n\n");
}
*/

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_token	*token;
	t_env	*env;
	t_cmd	*cmd;
	int		i;

	(void)argc;
	(void)argv;
	env = NULL;
	token = NULL;
	i = 1;
	ft_catch_env(envp, &env);
	while (i)
	{
		line = readline("💩 nugget 🐾$ ");
		//Ctrl+D: envia un NULL a readline -> salimos
		if (!line && ft_putendl_fd("exit", 2) && free_env(&env))
			exit(0);
		if (line && line[0] != '\0' && check_is_ok(line))
		{
			token = split_linker(line, &env);
			if(!token)
				continue;
			cmd = parser(token);
			// (void)cmd;
			printf("Printing command list...\n");
			print_cmd(cmd, 0);
			add_history(line);
		}
		free(line);
		free_token(&token);
		rl_on_new_line();
	}
	exit(0);
	return (0);
}
