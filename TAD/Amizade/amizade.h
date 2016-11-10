typedef struct a * ta_pont;

typedef struct a {
  int id1, id2, ativa;
  ta_pont ant, prox;
} Relacao;

typedef struct h {
  int qtd;
  ta_pont primeira, ultima;
} Amizade;

Amizade* iniciaListaAmizade();
void iniciarAmizade(Amizade *a, int id1, int id2);
void cancelarAmizade(Amizade *a, int id1, int id2);
