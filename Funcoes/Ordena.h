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
void ordenaMergesort(vetor *v, int inicio, int final);
void ordenaInsercao(vetor *v);
