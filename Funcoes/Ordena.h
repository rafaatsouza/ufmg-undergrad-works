typedef struct vetor {
    int tamanho;
    int *v;
} vetor;

void defineOrdenado(vetor *v);
vetor* criaVetorAleatorio(int min, int max, int tamanho);
vetor* criaVetorOrdenado(int tamanho, int reversamenteOrdenado);
vetor* criaVetorQuaseAleatorio(int min, int max, int tamanho);
void imprimeVetor(vetor *v);
int ordenaSelecao(vetor *v);
int ordenaBolha(vetor *v);
int ordenaShellsort(vetor *v);
void ordenaMergesort(int *v, int tamanho, int *mov);
int ordenaInsercao(vetor *v);
void ordenaQuicksort(vetor *v, int inicio, int final, int *mov);
int ordenaRadixsort(vetor *v);
int ordenaHeapSort(vetor *v);
