#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clean_buff()
{ 
  while (getchar() != EOF && getchar() != '\n');
}

int get_str(char *chaine, int taille)
{
  char *ptr = NULL;
  
  if(fgets(chaine, taille, stdin) != NULL)
    {
      ptr = strchr(chaine, '\n');
      if (ptr != NULL)
	{
	  *ptr = '\0';
	}
      else
	{
	  clean_buff();
	}
      return(1);
    }
  else
    {
      clean_buff();
      return(0);
    }
  
}
