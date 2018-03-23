int cpt = 1;

int rdm(int nb)
{
  int rdmNb;
  
  srand(time(NULL)+cpt);
  rdmNb = rand()%(nb)+1;
  cpt++;
  return(rdmNb);
}

void init_stack(int stack[CARD_NBR][2])
{
  int i;
  int j;
  
  for (i = 0; i < CARD_NBR; i++)
    {
      for (j = 0; j < 2; j++)
	{
	  stack[i][j] = 0;
	}
    }
}

char *cardNb_to_str(int nb)
{
  int i;
  int j;
  int tNb;
  int size;
  char *str = NULL;

  size = 2;
  i = 0;
  j = 1;
  if (nb > 9)
    {
      size = 3;
      j = 10;
    }
  str = malloc(size*sizeof(char));
  while (j >= 1)
    {
      tNb = nb / j + ZERO;
      nb = nb % j;
      j /= 10;
      str[i] = tNb;
      i++;
    }
  str[i] = '\0';
  return(str);
}

int *gen_card()
{
  int rdmNb;
  int rdmColor;
  int *stats = NULL;
  
  stats = malloc(2*sizeof(int));
  rdmNb = rdm(13);
  srand(time(NULL)*rdm(1000));
  rdmColor = rdm(4);
  stats[0] = rdmNb;
  stats[1] = rdmColor;
  return(stats);
}

Card *create_card(int *stats)
{
  Card *card = NULL;
  char *strName = NULL;

  card = malloc(sizeof(Card));
  switch (stats[0])
    {
    case 1:
      strcpy(card->name, "AS\0");
      card->value = 0;
      break;
    case 13:
      strcpy(card->name, "K\0");
      card->value = 10;
      break;
    case 12:
      strcpy(card->name, "Q\0");
      card->value = 10;
      break;
    case 11:
      strcpy(card->name, "J\0");
      card->value = 10;
      break;
    default:
      strName = cardNb_to_str(stats[0]);
      strcpy(card->name, strName);
      card->value = stats[0];
      free(strName);
      break;
    }
  
  switch (stats[1])
    {
    case 1:
      strcpy(card->sign, "pique");
      break;
    case 2:
      strcpy(card->sign, "coeur");
      break;
    case 3:
      strcpy(card->sign, "carreau");
      break;
    case 4:
      strcpy(card->sign, "trefle");
      break;
    }
  return(card);
}

void list_card(int stack[CARD_NBR][2], int *stats, int nb)
{
  int i;
  
  for (i = 0; i < 2; i++)
    {
      stack[nb][i] = stats[i];
    }
}

int validate_card(int stack[CARD_NBR][2], int *stats)
{
  int i;
  int j;
  int valid = 1;
  
  j = 0;
  for (i = 0; i < CARD_NBR; i++)
    {
      if (stack[i][j] == 0)
	{
	  break;
	}
      else if (stack[i][j] == stats[j] && stack[i][j+1] == stats[j+1])
	{
	  valid = 0;
	  break;
	}
    }
  return(valid);
}

Card *shuffle_deck()
{
  int stack[CARD_NBR][2];
  int i;
  int valid;
  Card *card = NULL;
  Card *prev = NULL;
  Card *first = NULL;
  int *stats = NULL;
  
  i = 0;
  
  while (i < CARD_NBR)
    {
      do
	{
	  stats = gen_card();
	  valid = validate_card(stack, stats);
	  if (!valid)
	    {
	      free(stats);
	    }
	} while (!valid);
      
      list_card(stack, stats, i);
      card = create_card(stats);
      free(stats);
      if (i == 0)
	{
	  first = card;
	}
      if (prev != NULL)
	{
	  prev->next = card;
	}
      prev = card;
      i++;
    }
  card->next = NULL;
  return(first);
}
