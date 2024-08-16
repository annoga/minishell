#include "../../inc/minishell.h"

int case_insensitive_strcmp(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return tolower((unsigned char)*a) - tolower((unsigned char)*b);
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

void swap_tokens(t_token *a, t_token *b)
{
    char *temp = a->token;
    a->token = b->token;
    b->token = temp;
}

void sort_alphabetic_token(t_token *head)
{
    if (head == NULL) {
        return;  // If the list is empty, nothing to sort
    }

    int swapped = 1;  // Assume at least one swap needs to be done
    t_token *ptr1;
    t_token *lptr = NULL;

    // Loop until no swaps occur
    while (swapped) {
        swapped = 0;
        ptr1 = head;

        // Traverse the list and compare adjacent nodes
        while (ptr1->next != lptr) {
            if (case_insensitive_strcmp(ptr1->token, ptr1->next->token) > 0) {
                swap_tokens(ptr1, ptr1->next);
                swapped = 1;  // Set swapped to true if any swap happened
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Reduce the unsorted part of the list
    }
}
