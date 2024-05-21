#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "readline/history.h"

void readline_simple(const char *str)
{
	
	char *line;
	line = readline(str);

	printf("is it a nugget?: %s\n", line);

	//free(line);
}

void addhistory_simple_notreal()
{
	char *line;
	int i = 0;
	
	while(++i <= 3)
	{
		line = readline("nugget (queda guardado en el historial): ");
		add_history(line);
	}
	/*
	while(1)
	{
		line = readline("nugget (no en el historial): ");
		if(line == NULL) 
			break;
	}
	*/
}

void replace_line()
{
	char *line;
	line = readline("nugget: ");
	printf("es un puto nugget? %s\n", line);
	rl_replace_line("this is new line: ", 0);
	rl_redisplay();
	line = readline("new nugget: ");
	printf("es un nuevo nugget? %s\n", line);

}

void new_line()
{

	int i = 0;
	char *line;

	while(++i <= 3)
	{
		line = readline("nugget: ");
		add_history(line);
		printf("es un puto nugget? %s\n", line);
		rl_on_new_line();
	}
}


void mi_primer_minishell()
{
	int i = 0;
	char *line;

	while(1)
	{
		line = readline("nugget: ");
		if(line[0] == 'd' && line[1] == '\0')
		{
			printf("you deleted the history\n");
			rl_clear_history();
		}
		else
		{
			add_history(line);
			//printf("es un puto nugget? %s\n", line);
		}
		
		rl_on_new_line();
	}
}


int main()
{

//	addhistory_simple_notreal();
//	readline_simple("nugget (sin limpiar historial): ");
//	rl_clear_history();
//	readline_simple("nugget (con limpiar historial): ");
//	new_line();
//	replace_line();
	mi_primer_minishell();


	return(0);
	
}
