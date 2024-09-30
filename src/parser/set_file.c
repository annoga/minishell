#include "../../inc/minishell.h"

static t_file	*create_file(t_token **token)
{
	t_file	*file;

	file = ft_calloc(sizeof(t_file), 1);
	if (!file)
		return (NULL);
	file->type = (*token)->type;
	while (*token && (*token)->syntaxis != FILES)
		*token = (*token)->next;
	if (!(*token))
		return (free(file), NULL);
	file->name = ft_strdup((*token)->token);
	if (!file->name)
		return (free(file), NULL);
	*token = (*token)->next;
	return (file);
}

void	set_file(t_cmd **cmd, t_token **token)
{
	t_file	*file;

	if (!(*cmd))
		(*cmd) = add_command(cmd);
	if (!(*cmd))
		return (lstclear(cmd, del_command));
	file = create_file(token);
	if (!file)
		return (lstclear(cmd, del_command));
	lst_add_back(&((*cmd)->files), file);
}