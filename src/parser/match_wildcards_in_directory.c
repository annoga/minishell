#include "../../inc/minishell.h"

static t_token *create_space_token(void)
{
    t_token *space_token;

    space_token = allocate_token();
    if (!space_token)
        return (NULL);
    space_token->token = strdup(" ");
    if (!space_token->token)
    {
        perror("strdup");
        free(space_token);
        return (NULL);
    }
    space_token->type = SPACE_TOKEN;
    space_token->is_quote = 0;
    return (space_token);
}

static void insert_space_tokens(t_token **tokens)
{
    t_token *current = *tokens;
    t_token *next;

    while (current)
    {
        next = current->next;
        t_token *space_token = create_space_token();
        if (!space_token)
            return;
        current->next = space_token;
        space_token->next = next;
        current = next;
    }
}

t_token	*match_wildcards_in_directory(const char *dir_path, const char *pattern)
{
	DIR		*dir;
	t_token	*new_tokens;
	t_token	*last_token;

	dir = open_directory(dir_path);
	if (!dir)
		return (NULL);
	last_token = NULL;
	new_tokens = NULL;
	process_directory_entries(dir, pattern, &new_tokens, &last_token);
	closedir(dir);

	insert_space_tokens(&new_tokens);

	return (new_tokens);
}