typedef struct m * t_prox;

typedef struct m {
  int x, y, val;
  t_prox next;
} Move;

typedef struct h {
  t_prox first, last;
} Historic;

typedef struct {
  int scoreTotal;
  int moveTotal;
  Historic *historic;
} Score;

typedef struct {
  char *name;
  int count_pokebolas, x, y;
  Score *score;
} Player;

void createPlayer(Player *p, int x, int y, char *n, int mapSize);
void andar(Player *p, int **map, int mapsize);
void printHistoric(Player *p, FILE *arq);
void DefineWinner(Player *p, int qtdPlayers, FILE *arq);
