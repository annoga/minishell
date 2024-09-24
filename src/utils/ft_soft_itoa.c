#include "../../inc/minishell.h"

void	ft_soft_itoa(t_env **tmp, int n)
{
	(*tmp)->value = ft_itoa(n);
	if (!(*tmp)->value)
		return_error("MALLOC");
}