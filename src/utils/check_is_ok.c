#include "../../inc/minishell.h"
int check_quotes(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if(line[i] == '\'')
        {
            i++;
            while(line[i] && line[i] != '\'')
                i++;
            if(!line[i])
                return(return_error("Error: missing single quote\n"), 0);
        
        }
        else if(line[i] == '"')
        {
            i++;
            while(line[i] && line[i] != '"')
                i++;
            if(!line[i])
                return(return_error("Error: missing double quote\n"), 0);
        }
        i++;
    }
    return (1);
}

int check_is_ok(char *line)
{
    printf("1. line: %s\n", line);
    if(!check_quotes(line))
        return (0);
    // if(!check_parenthesis(line))
    //     return (0);
    return (1);
}