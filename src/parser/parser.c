#include "../../inc/minishell.h"
void tokenize_env(t_token *tmp2, t_token *tmp, t_token *head)
{
    char *env;
    env = getenv(tmp->token);
    if(!env)
        env = ft_strdup("");
    else
        env = ft_strdup(env);
    printf("1. env token p: %p\n", env);
    tmp = tokenizer(env);
    add_top(tmp2, tmp);
    if (tmp)
        erase_one(&head, tmp2);
    else
    {
        printf("4. tmp2 token p: %p\n", tmp2->token);

        free(tmp2->token);
        tmp2->token = NULL;
        tmp2->token = env;
    }
    printf("4. tmp p: %p\n", tmp);
    tmp2 = tmp;
    printf("5. tmp2 p: %p\n", tmp2);
    printf("6. head p: %p\n", &head);
    tmp = tmp2;
}

t_token *prueba_env(t_token *head)
{
    t_token *tmp;
    t_token *tmp2;
    tmp = head;
    // char *env;
    while(tmp)
    {
        if(tmp->type == ENV)
        {
            printf("1. tmp p: %p\n", tmp);
            tmp2 = tmp;
            printf("2. tmp2 p: %p\n", tmp2);
            printf("3. head p: %p\n", head);
            tokenize_env(tmp2, tmp, head);
            // env = getenv(tmp->token);
            // if(!env)
            //     env = ft_strdup("");
            // tmp = tokenizer(env);
            // add_top(tmp2, tmp);
            // if (tmp)
            //     erase_one(&head, tmp2);
            // else
            // {
            //     free(tmp2->token);
            //     tmp2->token = env;
            // }
            // tmp = tmp2;
        }
        printf("7. tmp->next p: %p\n", tmp->next);
        tmp = tmp->next;
    }
    tmp = head;
    return (head);
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

