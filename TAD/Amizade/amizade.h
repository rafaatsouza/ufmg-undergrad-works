typedef struct a * t_pont;

typedef struct a {
  int id1, id2, t_cadastro;
  t_pont ant, prox;
} Relacao;

typedef struct h {
  int qtd;
  t_pont primeira, ultima;
} Amizade;

Amizade* iniciaListaAmizade();
int amizadeRepetida(Amizade *a, Relacao *r);
void insereAmizade(Amizade *a, int id1, int id2);
