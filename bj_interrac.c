char *ask_pseudo()
{
  char *pseudo;

  pseudo = malloc(LEN_MAX*sizeof(char));
  
  fprintf(stdout, "Bienvenue au jeu du BlackJack\nChoisissez un pseudo (14 caractères max)\n");
  get_str(pseudo, LEN_MAX);

  return(pseudo);
}

int ask_what_to_do(int turn)
{
  int option;
  char str[LEN_MAX];

  do
    {
      if (turn == 1)
	{
	  fprintf(stdout, "Quelle option jouer ? (1: carte / 2: rester / 3: doubler)");
	}
      else
	{
	  fprintf(stdout, "Quelle option jouer ? (1: carte / 2: rester)");
	}
      endl;
      get_str(str, LEN_MAX);
      option = string_to_nbr(str);
    } while (option < 1 || option > 3);
  return(option);
}

int ask_split()
{
  char str[LEN_MAX];
  int answ = 0;
  
  do
    {
      fprintf(stdout, "Voulez vous faire un split ? (1: oui / 0: non)");
      endl;
      get_str(str, LEN_MAX);
      answ = string_to_nbr(str);
    } while (answ != 1 && answ != 0);
  return(answ);
}

void show_card(Card card)
{
  Card *ptr = NULL;

  ptr = &card;
  printf(" __");
  endl;
  if (strlen(ptr->name) > 1)
    {
      printf("|%s|", ptr->name);
    }
  else
    {
      printf("|%s |", ptr->name);
    }
  endl;
  printf("|__|");
  endl;
}

void show_cards(Player plyr)
{
  Card *ptr = NULL;
  int i = 0;
  
  while (plyr.cards[i] != NULL)
    {
      switch (plyr.id)
	{
	case -1:
	  printf("Main du dealer");
	  break;
	case 1:
	  endl;
	  printf("Main %d du joueur", (i+1));
	  break;
	}
      endl;
      ptr = plyr.cards[i];
      while (ptr != NULL)
	{
	  show_card(*ptr);
	  ptr = ptr->next;
	}
      i++; 
    }
}

void show_deck(Card deck)
{
  int i = 0;
  Card *ptr = NULL;

  ptr = &deck;
  do
    {
      printf(" __");
      endl;
      if (strlen(ptr->name) > 1)
	{
	  printf("|%s|", ptr->name);
	}
      else
	{
	  printf("|%s |", ptr->name);
	}
      endl;
      printf("|__|");
      endl;
      ptr = ptr->next;
    } while (ptr != NULL);
}
