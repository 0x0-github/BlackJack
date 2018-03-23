typedef struct player_s Player;
typedef struct card_s Card;

struct player_s
{
  int id;
  char pseudo[MAX_LENGTH];
  int cash;
  int score[3];
  Card *cards[3];
  Player *next;
};

struct card_s
{
  char name[STRUCT_CARD_MAX-4];
  char sign[STRUCT_CARD_MAX];
  int value;
  Card *next;
};
