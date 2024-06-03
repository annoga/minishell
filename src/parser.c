#include "../inc/minishell.h"


t_token *check_bonus_token(t_token *head)
{
    t_token *tmp;
    int     type_bonus;

    tmp = head;
    type_bonus = 0;
    while(tmp)
    {
        if(tmp->type == AND)
            type_bonus = AND;
        else if(tmp->type == OR)
            type_bonus = OR;
        tmp = tmp->next;
    }
    tmp = head;
    tmp = assign_bonus_token(tmp, type_bonus);
    return (tmp);
}

t_token *assign_bonus_token(t_token *head, int type_bonus)
{
    t_token *tmp;

    tmp = head;
    while(tmp)
    {
        if(type_bonus == AND)
            tmp->and = 1;
        else if(type_bonus == OR)
            tmp->or = 1;
        if(tmp->type == PAREN)
        {
            printf("hoal\n");
            tmp = tokenizer(tmp->token);
        }
        tmp = tmp->next;
    }
    tmp = head;
    return (tmp);
}

