typedef struct vetor {
    int tamanho;
    int *v;
} vetor;

void defineOrdenado(vetor *v);
vetor* criaVetorAleatorio(int min, int max, int tamanho);
vetor* criaVetorOrdenado(int tamanho, int reversamenteOrdenado);
vetor* criaVetorQuaseAleatorio(int min, int max, int tamanho);
void imprimeVetor(vetor *v);
int ordenaSelecao(vetor *v, int *comp);
int ordenaBolha(vetor *v, int *comp);
int ordenaShellsort(vetor *v, int *comp);
void ordenaMergesort(int *v, int tamanho, int *mov, int *comp);
int ordenaInsercao(vetor *v, int *comp);
void ordenaQuicksort(vetor *v, int inicio, int final, int *mov, int *comp);
int ordenaRadixsort(vetor *v);
int ordenaHeapSort(vetor *v, int *comp);
