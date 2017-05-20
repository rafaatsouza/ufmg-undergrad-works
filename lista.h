typedef struct i * t_liga;

typedef struct i {
  int index;
  t_liga prox;
} item;

typedef struct l {
	int qtd;
	t_liga primeiro, ultimo;
} lista;

lista* criaListaVazia();
int listaVazia(lista *l);
void adicionaItemLista(lista *l, int v);
void liberaLista(lista *l);
void printaSequencia(lista *l);