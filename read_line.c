#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

void readline_simple()
{
	
	char *line;
	line = readline("nugget: ");

	printf("is it a nugget?: %s\n", line);

	free(line);
}

void addhistory_simple_notreal()
{
	char *line;
	int i;
	
	for(i = 0; i < 5; i++) 
	{
		line = readline("Ingresa una línea de texto: ");
		add_history(line);
	}
	while(1)
	{
		line = readline("Ingresa una línea de texto (o presiona ctrl + c para salir): ");
		if(line != NULL)
		{
			printf("La línea ingresada es: %s\n", line);
		}
		else 
		{
			break;
		}
	}
}


int main()
{
	//readline_simple();
	addhistory_simple_notreal();
	
	return(0);
	
}
