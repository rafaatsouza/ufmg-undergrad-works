typedef struct a * ta_pont;

typedef struct m * tm_pont;

typedef struct m {
  int t_cadastro, t_cancelamento;
  tm_pont prox;
} Momento;

typedef struct a {
  int id1, id2, ativa;
  Momento *momento;
  ta_pont ant, prox;
} Relacao;

typedef struct h {
  int qtd;
  ta_pont primeira, ultima;
} Amizade;

Amizade* iniciaListaAmizade();
int amizadeRepetida(Amizade *a, Relacao *r);
void iniciarAmizade(Amizade *a, int id1, int id2, int tempo);
void cancelarAmizade(Amizade *a, int id1, int id2, int tempo);
