#include "../../inc/minishell.h"

t_cmd	*add_command(t_cmd **cmd_lst)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(t_cmd), 1);
	if (!command)
	{
		lstclear(cmd_lst, del_command);
		return (NULL);
	}
	lst_add_back(cmd_lst, command);
	return (command);
}