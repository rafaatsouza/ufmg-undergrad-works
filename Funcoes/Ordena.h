typedef struct vetor {
    int tamanho;
    int *v;
} vetor;

void defineOrdenado(vetor *v);
vetor* criaVetor(int min, int max, int tamanho);
void imprimeVetor(vetor *v);
void ordenaSelecao(vetor *v);
void ordenaBolha(vetor *v);
void ordenaShellsort(vetor *v);
void ordenaMergesort(int *v, int tamanho);
void ordenaInsercao(vetor *v);
void ordenaQuicksort(vetor *v, int inicio, int final);
void ordenaRadixsort(vetor *v);
