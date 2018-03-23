int idD = -1;
int id = 0;

void init_player(Player *plyr, int idP, char *pseudo, int cash, Player *next)
{
  Card *zero;

  zero = malloc(sizeof(Card));
  zero->value = 0;
  zero->next = NULL;
  plyr->id = idP;
  if (pseudo != NULL)
    {
      strcpy(plyr->pseudo, pseudo);
    }
  plyr->cash = cash;
  plyr->score[0] = 0;
  plyr->score[1] = 0;
  plyr->cards[0] = zero;
  plyr->cards[1] = NULL;
  plyr->cards[2] = NULL;
  plyr->next = next;
  id++;
}

void init_dealer(Player *dlr)
{
  init_player(dlr, idD, D_PSEUDO, CASH_D, NULL);
  idD--;
}

void free_cards(Card *card)
{
  if (card != NULL)
    {
      free_cards(card->next);
    }
  free(card);
  card = NULL;
}

void reinit_players(Player *plyr, Player *dlr)
{
  int i = 0;
  
  while (plyr->cards[i] != NULL)
    {
      free_cards(plyr->cards[i]);
      endl;
      plyr->cards[i] = NULL;
      i++;
    }
  free_cards(dlr->cards[0]);
  init_player(plyr, plyr->id, NULL, plyr->cash, dlr);
  init_player(dlr, dlr->id, NULL, dlr->cash, NULL);
}

int get_score(Player plyr, int nb)
{
  int score = 0;
 
  while (plyr.cards[nb] != NULL)
    {
      score += plyr.cards[nb]->value;
      plyr.cards[nb] = plyr.cards[nb]->next;
    }
  return(score);
}

int flop_as()
{
  char strVal[4];
  int value;
  int i = 0;
  
  do
    {
      printf("Vous avez tiré un AS, quelle valeur lui donner ? (1 - 11)\n");
      get_str(strVal, 4);
      value = string_to_nbr(strVal);
    } while (value != 1 && value != 11);
  return(value);
}

int dlr_flop_as(Player *dlr)
{
  int value;

  printf("Le dealer tire un as");
  endl;
  if (dlr->score[0] <= 10)
    {
      value = 11;
    }
  else
    {
      value = 1;
    }
  printf("L'as aura pour valeur %d", value);
  endl;
  return(value);
}

void draw_card(Player *plyr, Card *card, int nb)
{
  Card *first = NULL;
  Card *save = NULL;
  Card *cpy = NULL;

  cpy = malloc(sizeof(Card*));
  *cpy = *card;
  cpy->next = NULL;
  
  if (card->value == 0 && plyr->id != -1)
    {
      cpy->value = flop_as();
    }
  else if (card->value == 0 && plyr->id == -1)
    {
      cpy->value = dlr_flop_as(plyr);
    }
  if (plyr->cards[nb]->value == 0)
    {
      plyr->cards[nb] = cpy;
    }
  else
    {
      first = plyr->cards[nb];
      while (plyr->cards[nb]->next != NULL)
	{
	  plyr->cards[nb] = plyr->cards[nb]->next;
	}
      plyr->cards[nb]->next = cpy;
      plyr->cards[nb] = first;
    }
  *card = *(card->next);
  plyr->score[nb] = get_score(*plyr, nb);
}

int bet(Player *plyr, Player *dlr)
{
  char bet[BET_SIZE];
  int valide = 1;
  int nb;

  do
    {
      printf("Combien voulez vous parier ?\n");
      get_str(bet, BET_SIZE);
      nb = string_to_nbr(bet);
      if (nb > CASH_D || nb < 1)
	{
	  printf("Nombre non valide\nLe nombre doit etre compris entre 0 et %d\n", CASH_D);
	  valide--;
	}
      else if (nb > plyr->cash || nb > dlr->cash)
	{
	  printf("Mise trop elevee !\n");
	  printf("Votre cash : %d € - Dealer cash : %d €\n", plyr->cash, dlr->cash);
	  valide--;
	}
      else
	{
	  valide = 1;
	}
    } while (valide != 1);
  plyr->cash -= nb;
  dlr->cash -= nb;
  printf("Cash : %d € - Dealer cash : %d €\n", plyr->cash, dlr->cash);

  return(nb*2);
}

int splitable(Player plyr)
{
  int valid = 1;

  if (strcmp(plyr.cards[0]->name, plyr.cards[0]->next->name) != 0)
    {
      valid = 0;
    }
  return(valid);
}

void split(Player *plyr)
{
  int score;
  Card *temp = plyr->cards[0]->next;
  
  score = temp->value;
  plyr->cards[1] = temp;
  plyr->cards[1]->next = NULL;
  plyr->cards[0]->next = NULL;
  plyr->score[0] -= score;
  plyr->score[1] = score;
}

int init_game(Player *plyr, Player *dlr, Card *deck, int *splt)
{
  int i;
  int pot;
  int j = 0;
  
  pot = bet(plyr, dlr);
  for (i = 0; i < 2; i++)
    {
      draw_card(plyr, deck, 0);
    }
  show_cards(*plyr);
  endl;
  printf("Score de la main 1: %d", plyr->score[0]);
  endl;
  *splt = splitable(*plyr);
  if (*splt)
    {
      if (ask_split())
	{
	  split(plyr);
	}
    }
  draw_card(dlr, deck, 0);
  endl;
  show_cards(*dlr);
  endl;
  return(pot);
}

int insurance(Player *plyr, Player *dlr, int pot)
{
  char str[LEN_MAX] = "";
  char str2[LEN_MAX] = "";
  int answ;
  int bet = 0;
  int betMax = pot / 2;
  
  do
    {
      fprintf(stdout, "Voulez vous prendre l'assurance ? (1: oui / 2: non)\n");
      get_str(str, LEN_MAX);
      answ = string_to_nbr(str);
    } while (answ != 1 && answ != 2);
  if (answ == 1)
    {
      do
	{
	  fprintf(stdout, "Combien miser ? (max : %d €)\n", betMax);
	  get_str(str2, LEN_MAX);
	  bet = string_to_nbr(str2);
	} while (bet > betMax || bet < 0);
      plyr->cash -= bet;
    }
  
  return(bet);
}

int blackJack(Player *plyr, Player *dlr, Card *deck, int *pot)
{
  int gain;
  int bj = 0;
  int insure;
    
  gain = *pot * 1.5;
  if (plyr->score[0] == 21 && dlr->cards[0]->value != 11)
    {
      bj = 1;
    }
  else if (plyr->score[0] == 21 && dlr->cards[0]->value == 11)
    {
      printf("Le dealer possede un AS ! Il va tirer une seconde carte");
      endl;
      insure = insurance(plyr, dlr, *pot);
      draw_card(dlr, deck, 0);
      show_cards(*dlr);
      if (dlr->score[0] == 21)
	{
	  printf("Pas de chance... Les mains sont declarées nulles");
	  if (insure)
	    {
	      plyr->cash += insure;
	      insure *= 2;
	      fprintf(stdout, "Vous aviez souscrit à l'assurance !\n vous gagnez %d €", insure);
	      endl;
	      dlr->cash -= insure;
	      plyr->cash += insure;
	      
	    }
	  endl;
	  plyr->cash += *pot / 2;
	  dlr->cash += *pot / 2;
	  *pot = 0;
	}
      else
	{
	  bj = 1;
	}
    }
  if (bj == 1)
    {
      printf("Bravo c'est un BlackJack !\nVous remportez un pot de %d €", gain);
      endl;
      if (insure)
	{
	  printf("Vous perder cependant les %d € de l'assurance !\n", insure);
	  dlr->cash += insure;
	  endl;
	}
      plyr->cash += gain;
      dlr->cash -= *pot / 2;
      *pot = 0;
    }
  return(bj);
}

void take_annother(Player *plyr, Card *deck, int nb)
{
  printf("Vous piochez une carte");
  endl;
  draw_card(plyr, deck, nb);
  show_cards(*plyr);
  endl;
  printf("Score de la main %d: %d\n", (nb+1), plyr->score[nb]);
}

int double_card(Player *plyr, Card *deck, int *pot, int nb)
{
  int valid = 1;
  int nbr = *pot / 2;

  if ((plyr->cash - nbr) > 0)
    {
      plyr->cash -= nbr;
      *pot += nbr;
      printf("Vous payez %d € il vous reste %d €\n", nbr, plyr->cash);
      take_annother(plyr, deck, nb);
    }
  else
    {
      valid = 0;
    }
  return(valid);
}

int dlr_move(Player *dlr, Card *deck)
{
  int over = 0;
  
  while (dlr->score[0] < 17)
    {
      printf("Le dealer tire une carte");
      endl;
      draw_card(dlr, deck, 0);
      show_cards(*dlr);
      endl;
      printf("Le score du dealer est de %d", dlr->score[0]);
      endl;
    }
  if (dlr->score[0] > 21)
    {
      over = 1;
    }
  return(over);
}

void set_winner(Player *plyr, Player *dlr, int *pot, int split)
{
  int nb = 0;
  int gain = *pot;

  if (split)
    {
      gain = *pot / 2;
    }
  while (plyr->cards[nb] != NULL)
    {
      if (dlr->score[0] > 21 && plyr->score[nb] <= 21 || plyr->score[nb] > dlr->score[0] && plyr->score[nb] <= 21)
	{
	  printf("Vous gagnez un pot de %d € avec un score de %d contre %d", gain, plyr->score[nb], dlr->score[0]);
      endl;
      plyr->cash += *pot;
	}
      else if ((plyr->score[nb] <= 21 && dlr->score[0] <= 21 && plyr->score[nb] == dlr->score[0]) || (plyr->score[nb] > 21 && dlr->score[0] > 21))
	{
	  printf("Egalité, les mises sont déclarées nulles !");
	  endl;
	  endl;
	  plyr->cash += *(pot) / 2;
	  dlr->cash += *(pot) / 2;
	}
      else
	{
	  printf("Le dealer gagne %d € avec un score de %d contre %d", gain, dlr->score[0], plyr->score[nb]);
	  endl;
	  dlr->cash += *pot;
	}
      nb++;
    }
  *pot = 0;
}

int set_end(Player *plyr, Player *dlr)
{
  int end = 1;
  if (plyr->cash == 0)
    {
      printf("Il ne vous reste plus de cash... Vous avez perdu !");
      endl;
    }
  else if (dlr->cash == 0)
    {
      printf("Il ne reste plus de cash au dealer... Vous avez gagné !");
      endl;
    }
  else
    {
      printf("Votre cash : %d - Dealer cash : %d", plyr->cash, dlr->cash);
      endl;
      end = 0;
    }
  return(end);
}

