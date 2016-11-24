typedef struct vetor {
    int tamanho;
    int *v;
} vetor;

void defineOrdenado(vetor *v);
vetor* criaVetorAleatorio(int min, int max, int tamanho);
vetor* criaVetorOrdenado(int tamanho, int reversamenteOrdenado);
vetor* criaVetorQuaseAleatorio(int min, int max, int tamanho);
void imprimeVetor(vetor *v);
void ordenaSelecao(vetor *v);
void ordenaBolha(vetor *v);
void ordenaShellsort(vetor *v);
void ordenaMergesort(int *v, int tamanho);
void ordenaInsercao(vetor *v);
void ordenaQuicksort(vetor *v, int inicio, int final);
void ordenaRadixsort(vetor *v);
void ordenaHeapSort(vetor *v);
