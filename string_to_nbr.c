#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int string_to_nbr(char *nbr)
{
  int resultat = 0;
  int i = 0;
  float multiple = 0.1;

  while (nbr[i] != '\0')
    {
      multiple *= 10;
      i++;
    }
  i = 0;
  while (nbr[i] != '\0')
    {
      resultat += (nbr[i] - 48) * multiple;
      multiple /= 10;
      i++;
    }
  return (resultat);
}
