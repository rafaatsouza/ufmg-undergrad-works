#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"
#include "Ordena.h"

#define less(A, B) (A < B)

//informa se o vetor está ordenado ou não
void defineOrdenado(vetor *v){
    int i;
    for(i=0;i<v->tamanho;i++){
        if(i != 0){
            if(v->v[i] < v->v[i-1]){
                printf("Vetor nao esta ordenado:\n");
                return;
            }
        }
    }
    printf("Vetor esta ordenado:\n");
}

//cria uma nova variável do tipo vetor
vetor* criaVetor(int min, int max, int tamanho){
    int i;
    vetor *v = (vetor*)malloc(sizeof(vetor));

    v->tamanho = tamanho;
    v->v = (int*)malloc(sizeof(int) * tamanho);

    for(i=0;i<tamanho;i++){
        v->v[i] = retornaAleatorio(min,max);
    }
    return v;
}

//imprime todos os elementos de um vetor
void imprimeVetor(vetor *v){
    int i;
    for(i=0;i<v->tamanho;i++){
        printf("%d ", v->v[i]);
    }
    printf("\n");
}

//ordena vetor por método seleção
void ordenaSelecao(vetor *v){
    int i, j, Min, x;
    for (i=0;i<v->tamanho;i++){
        Min = i;
        for (j=i+1;j<v->tamanho;j++)
            if (v->v[j] < v->v[Min])
                Min = j;
        x = v->v[Min];
        v->v[Min] = v->v[i];
        v->v[i] = x;
    }
}

//ordena vetor por método bolha
void ordenaBolha(vetor *v){
    int i, j, x;
    for (i=0;i<= v->tamanho;i++){
        for (j=0;j<=(v->tamanho-i);j++){
            if(j<v->tamanho-1){
                if (v->v[j] > v->v[j+1]){
                    x = v->v[j];
                    v->v[j] = v->v[j+1];
                    v->v[j+1] = x;
                }
            }
        }
    }
}

//ordena vetor por método shellsort
void ordenaShellsort(vetor *v){
    int i, j, x, h = 1;
    do h = h * 3 + 1; while (h < v->tamanho);
    do{
        h /= 3;
        for (i = 0; i <= v->tamanho; i=i+h){
            x = v->v[i];
            j = i;
            while (v->v[j - h] >= x){
                v->v[j] = v->v[j - h];
                j -= h;
                if (j < h) break;
            }
            v->v[j] = x;
        }
    } while (h != 1);
}

void merge(int *v, int *esquerda, int cont_e, int *direita, int cont_d){
    int i = 0, j = 0, k =0;

	while(i<cont_e && j< cont_d) {
		if(esquerda[i]  < direita[j]) v[k++] = esquerda[i++];
		else v[k++] = direita[j++];
	}
	while(i < cont_e) v[k++] = esquerda[i++];
	while(j < cont_d) v[k++] = direita[j++];
}

//ordena vetor por método mergesort
void ordenaMergesort(int *v, int tamanho){
    int meio,i, *esquerda, *direita;
    if(tamanho < 2) return;

    meio = tamanho/2;
    esquerda = (int*)malloc(meio*sizeof(int));
    direita = (int*)malloc((tamanho - meio)*sizeof(int));

    for(i = 0;i<meio;i++) esquerda[i] = v[i];
    for(i = meio;i<tamanho;i++) direita[i-meio] = v[i];

    ordenaMergesort(esquerda,meio);
    ordenaMergesort(direita,tamanho-meio);
    merge(v,esquerda,meio,direita,tamanho-meio);
    free(esquerda);
    free(direita);
}

//ordena vetor por método inserção
void ordenaInsercao(vetor *v){
    int j, i, x;
    for(j=1;j<v->tamanho;j++){
        x = v->v[j];
        i = j-1;
        while(i>=0 && v->v[i] > x){
            v->v[i+1] = v->v[i];
            i--;
        }
        v->v[i+1] = x;
    }
}

//divide os vetores para ordenação de método quicksort
int separaQuick (vetor *v, int inicio, int final) {
   int c = v->v[inicio], i = inicio+1, j = final, t;
   while (i <= j) {
      if (v->v[i] <= c) ++i;
      else if (c < v->v[j]) --j;
      else {
         t = v->v[i], v->v[i] = v->v[j], v->v[j] = t;
         ++i; --j;
      }
   }
   v->v[inicio] = v->v[j], v->v[j] = c;
   return j;
}

//ordena vetor por método quicksort
void ordenaQuicksort(vetor *v, int inicio, int final) {
   int j;
   while (inicio < final) {
      j = separaQuick(v, inicio, final);
      ordenaQuicksort(v, inicio, j-1);
      inicio = j + 1;
   }
}

//order vetor por método radixsort
void ordenaRadixsort(vetor *v) {
    int i, digito = 1, aux[v->tamanho], maior = retornaMax(v->v, v->tamanho);

    while (maior / digito > 0){
        int bucket[10] = { 0 };

        for (i = 0; i < v->tamanho; i++)
            bucket[(v->v[i] / digito) % 10]++;

        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];

        for (i = v->tamanho - 1; i >= 0; i--)
            aux[--bucket[(v->v[i] / digito) % 10]] = v->v[i];

        for (i = 0; i < v->tamanho; i++)
            v->v[i] = aux[i];

        digito *= 10;
    }
}
