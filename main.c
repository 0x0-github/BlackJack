#define CARD_NBR 52
#define ZERO 48
#define D_PSEUDO "Dealer\0"
#define CASH_D 100000
#define CASH_MAX 2000
#define BET_SIZE 7
#define LEN_MAX 14
#define endl printf("\n")
#define MAX_LENGTH 15
#define STRUCT_CARD_MAX 7

#include "includes.c"
#include "bj_struct.c"
#include "prototypes.h"
#include "bj_deck_func.c"
#include "bj_interrac.c"
#include "bj_game_func.c"
#include "get_str.c"
#include "string_to_nbr.c"

int main()
{
  int bj;
  int pot;
  int option;
  int stay;
  int overP;
  int overD;
  int end = 0;
  int doubl;
  int split;
  int i;
  int nbHand;
  int turn;
  int insure = 0;
  Player plyr;
  Player dlr;
  Card *deck = NULL;
  char *pseudo = NULL;

  pseudo = ask_pseudo();
  printf("Que la partie commence %s !\n", pseudo);
  init_dealer(&dlr);
  init_player(&plyr, id, pseudo, CASH_MAX, &dlr);
  free(pseudo);
  do
    {
      bj = 0;
      option = 0;
      stay = 1;
      overP = 0;
      overD = 0;
      turn = 1;
      split = 0;
      free_cards(deck);
      deck = NULL;
      deck = shuffle_deck();
      do
	{
	  reinit_players(&plyr, &dlr);
	  pot = init_game(&plyr, &dlr, deck, &split);
	  bj = blackJack(&plyr, &dlr, deck, &pot);
	} while (bj);
      
      if (dlr.score[0] == 11)
	{
	  insure = insurance(&plyr, &dlr, pot);
	}
      while (stay && !overP)
	{
	  if (split)
	    {
	      nbHand = 2;
	      stay = 2;
	    }
	  else
	    {
	      nbHand = 1;
	    }
	  while (i < nbHand)
	    {
	      endl;
	      printf("---main %d---\n", i+1);
	      option = ask_what_to_do(turn);
	      switch (option)
		{
		case 1:
		  take_annother(&plyr, deck, i);
		  break;
		case 2:
		  if  (nbHand == 2)
		    {
		      stay--;
		    }
		  else
		    {
		      stay = 0;
		    }
		  break;
		case 3:
		  if (turn == 1)
		    {
		      if (double_card(&plyr, deck, &pot, 0))
			{
			  doubl = pot / 2;
			  dlr.cash -= doubl;
			  pot += doubl;
			  stay = 0;
			}
		      else
			{
			  printf("Vous n'avez pas assez d'argent !");
			  endl;
			}
		    }
		  else
		    {
		      printf("Vous ne pouvez doubler qu'au deux premières cartes");
		      endl;
		    }
		  break;
		}
	      if (plyr.score[0] > 21 || plyr.score[1] > 21)
		{
		  printf("Vous depassez 21...");
		  endl;
		  if (nbHand == 1 || (nbHand == 2 && i == 1))
		    {
		      overP = 1;
		    }
		}
	      turn++;
	      i++;
	    }
	  i = 0;
	}
      if (insure)
	{
	  printf("Le dealer tire une carte");
	  endl;
	  draw_card(&dlr, deck, 0);
	  show_cards(dlr);
	  if (dlr.score[0] == 21)
	    {
	      plyr.cash += insure;
	      insure *= 2;
	      printf("Vous aviez souscrit à l'asssurance !\nVous touchez %d €\n", insure);
	      dlr.cash -= insure;
	      plyr.cash += insure;
	    }
	  else
	    {
	      dlr.cash += insure;
	    }
	}
      overD = dlr_move(&dlr, deck);
      set_winner(&plyr, &dlr, &pot, split);
      end = set_end(&plyr, &dlr);
    } while (!end);
  return(0);
}
