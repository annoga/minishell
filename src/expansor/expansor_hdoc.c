#include "../../inc/minishell.h"



t_token *expansor_hdoc(t_token *head, t_env **env, int is_hdoc, int is_quoted)
{
    t_token *tmp = head;
    t_token *tmp2;
    (void)is_hdoc;

    while (tmp)
    {
        if (tmp->type == ENV && !is_quoted)
        {
            tmp2 = tmp;
            tokenize_env(&tmp2, &tmp, &head, env);
        }
        // else if(tmp->type SINGLE_QUOTE)
        // {
            
        // }
        tmp = tmp->next;
    }
    return head;
}