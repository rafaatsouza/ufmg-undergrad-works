typedef struct n * n_prox;

typedef struct n {
  int val;
  n_prox abaixo;
} Num;

typedef struct {
    int count_numeros, result;
    n_prox topo;
} pilhaOperacoes;

pilhaOperacoes* createPV();
void addNumPilha(pilhaOperacoes *po, int num);
void fazOperacao(pilhaOperacoes *po, int iSoma);
