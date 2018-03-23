
//bj_deck_func.c
int rdm(int nb);

void init_stack(int stack[CARD_NBR][2]);

char *cardNb_to_str(int nb);

int *gen_card();

Card *create_card(int *stats);

void list_card(int stack[CARD_NBR][2], int *stats, int nb);

int validate_card(int stack[CARD_NBR][2], int *stats);

Card *shuffle_deck();

//bj_game_func.c
void init_player(Player *plyr, int idP, char *pseudo, int cash, Player *next);

void init_dealer(Player *dlr);

void free_cards(Card *card);

void reinit_players(Player *plyr, Player *dlr);

int get_score(Player plyr, int nb);

int flop_as();

int dlr_flop_as(Player *dlr);

void draw_card(Player *plyr, Card *card, int nb);

int bet(Player *plyr, Player *dlr);

int splitable(Player plyr);

void split(Player *plyr);

int init_game(Player *plyr, Player *dlr, Card *deck, int *splt);

int insurance(Player *plyr, Player *dlr, int pot);

int blackJack(Player *plyr, Player *dlr, Card *deck, int *pot);

void take_annother(Player *plyr, Card *deck, int nb);

int double_card(Player *plyr, Card *deck, int *pot, int nb);

int dlr_move(Player *dlr, Card *deck);

void set_winner(Player *plyr, Player *dlr, int *pot, int split);

int set_end(Player *plyr, Player *dlr);

//bj_interract.c
char *ask_pseudo();

int ask_what_to_do(int turn);

int ask_split();

void show_card(Card card);

void show_cards(Player plyr);

void show_deck(Card deck);

//get_str.c
void clean_buff();

int get_str(char *chaine, int taille);

//string_to_nbr.c
int string_to_nbr(char *nbr);


































