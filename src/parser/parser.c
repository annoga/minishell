#include "../../inc/minishell.h"
void prueba_env(t_token *head)
{
    t_token *tmp;
    tmp = head;
    printf("prueba_env\n");
    while(tmp)
    {
        printf("token: %s\n", tmp->token);
        if(tmp->type == ENV)
        {
            // getenv(tmp->token);
            printf("ENV: %s\n", getenv(tmp->token));
        }
        tmp = tmp->next;
    }
}

// t_token *check_bonus_token(t_token *head)
// {
//     t_token *tmp;
//     int     type_bonus;

//     tmp = head;
//     type_bonus = 0;
//     while(tmp)
//     {
//         if(tmp->type == AND)
//             type_bonus = AND;
//         else if(tmp->type == OR)
//             type_bonus = OR;
//         tmp = tmp->next;
//     }
//     tmp = head;
//     tmp = assign_bonus_token(tmp, type_bonus);
//     return (tmp);
// }

// t_token *assign_bonus_token(t_token *head, int type_bonus)
// {
//     t_token *tmp;
//     t_token *tmp2;

//     tmp = head;
//     tmp2 = head;
//     while(tmp2)
//     {
//         if(type_bonus == AND)
//             tmp2->and = 1;
//         else if(type_bonus == OR)
//             tmp2->or = 1;
//         if(tmp2->type == PAREN)
//         {
//             // tmp2 = tokenizer(tmp->token);
//             add_token(&tmp, tokenizer(tmp->token));
//         }
//         tmp2 = tmp2->next;
//     }
//     return (tmp);
// }

