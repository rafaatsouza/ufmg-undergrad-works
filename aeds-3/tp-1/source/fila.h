typedef struct fv {
    int *v, qtdNumeros;
} filaNumeros;

filaNumeros* criaFilaVazia(int maxTam);
int filaVazia(filaNumeros *fv);
void enfileira(filaNumeros *fv, int v);
int desenfileira(filaNumeros *fv);
void liberaFila(filaNumeros *fv);
