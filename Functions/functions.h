typedef struct localizacao {
	int x;
	int y;
	float dx;
	float dy;
	bool active;
} location;

typedef struct Bomb {
	int x;
	int y;
	int seconds;
	double raio;
	bool active;
} bomb;

int returnRandom(int min, int max);
void PersegueLocation(location enemy_l[], int qtd_enemies, location *target);
void createBomb(bomb b[], int qtd_bombs, location *bomber_l, int time, double range);
bool checkKill(bomb *b, location *enemy);
void createLocationEnemies(location enemy[], int qtd_enemies, location *bomber_l, int max_x, int max_y, int size);
void createLocationBomber(location *bomber_l, int max_x, int max_y, int size);
void checkDeath(location *bomber, location e[], int qtd_enemies,  int size);
void MoveEnemies(location e[], int qtd_enemies, int size, int max_x, int max_y);
void defineDelta(location enemies[], int qtd_enemies, float x, int fase);
float returnRecorde(float pontuacao);