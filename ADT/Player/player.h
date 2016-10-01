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
  int name_count;
  int count_pokebolas;
  int x, y;
  Score *score;
} Player;

void createPlayer(Player *p, int x, int y, char *n, int name_count, int mapSize);
void MovePlayer(Player *p, int **map, int mapsize);
