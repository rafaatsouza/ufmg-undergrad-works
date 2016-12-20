#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Ordena.h"

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

//cria uma nova variável do tipo vetor com os elementos aleatorios
vetor* criaVetorAleatorio(int min, int max, int tamanho){
    int i;
    vetor *v = (vetor*)malloc(sizeof(vetor));

    v->tamanho = tamanho;
    v->v = (int*)malloc(sizeof(int) * tamanho);

    srand((unsigned)time(NULL));
    for(i=0;i<tamanho;i++){
        v->v[i] = (min + (rand()%max));
    }
    return v;
}

//cria uma nova variável do tipo vetor com os elementos ordenados de forma crescente/decrescente
vetor* criaVetorOrdenado(int tamanho, int reversamenteOrdenado){
    int i;
    vetor *v = (vetor*)malloc(sizeof(vetor));

    v->tamanho = tamanho;
    v->v = (int*)malloc(sizeof(int) * tamanho);

    if(reversamenteOrdenado == 0){
        for(i=0;i<tamanho;i++){
            v->v[i] = i+1;
        }
    } else {
        for(i=0;i<tamanho;i++){
            v->v[i] = tamanho-i;
        }
    }
    return v;
}

vetor* criaVetorQuaseAleatorio(int min, int max, int tamanho){
    int i, j;
    vetor *v = (vetor*)malloc(sizeof(vetor));

    v->tamanho = tamanho;
    v->v = (int*)malloc(sizeof(int) * tamanho);

    for(i=0;i<(tamanho-(tamanho/10));i++){
        v->v[i] = i+1;
    }
    srand((unsigned)time(NULL));
    for(j=i;j<tamanho;j++){
        v->v[j] = (min + (rand()%max));
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
int ordenaSelecao(vetor *v, int *comp){
    int i, j, Min, x, mov = 0;
    for (i=0;i<v->tamanho;i++){
        Min = i;
        for (j=i+1;j<v->tamanho;j++){
            *comp = *comp + 1;
            if (v->v[j] < v->v[Min]){
                Min = j;
            }
        }
        mov = mov + 3;
        x = v->v[Min];
        v->v[Min] = v->v[i];
        v->v[i] = x;
    }
    return mov;
}

//ordena vetor por método bolha
int ordenaBolha(vetor *v, int *comp){
    int i, j, x, mov = 0;
    for (i=0;i<= v->tamanho;i++){
        for (j=0;j<=(v->tamanho-i);j++){
            if(j<v->tamanho-1){
                if (v->v[j] > v->v[j+1]){
                    x = v->v[j];
                    v->v[j] = v->v[j+1];
                    v->v[j+1] = x;
                    mov = mov + 3;
                }
                *comp = *comp + 1;
            }
        }
    }
    return mov;
}

//ordena vetor por método shellsort
int ordenaShellsort(vetor *v, int *comp){
    int chave, k, aux, mov = 0, i = (v->tamanho - 1) / 2;

    while(i != 0) {
        do {
            chave = 1;
            for(k = 0; k < v->tamanho - i; ++k) {
                if(v->v[k] > v->v[k + i]) {
                    aux = v->v[k];
                    v->v[k] = v->v[k + i];
                    v->v[k + i] = aux;
                    chave = 0;
                    mov = mov + 3;
                }
                *comp = *comp + 1;
            }
        } while(chave == 0);
        i = i / 2;
    }
    return mov;
}

//concatena os dois vetores em um só no vetor original
void merge(int *v, int *esquerda, int cont_e, int *direita, int cont_d, int *mov, int *comp){
    int i = 0, j = 0, k =0;

	while(i<cont_e && j< cont_d) {
        *comp = *comp + 1;
		if(esquerda[i]  < direita[j]) v[k++] = esquerda[i++], *mov = *mov + 1;
		else v[k++] = direita[j++], *mov = *mov + 1;
	}
	while(i < cont_e) v[k++] = esquerda[i++], *mov = *mov + 1;
	while(j < cont_d) v[k++] = direita[j++], *mov = *mov + 1;
}

//ordena vetor por método mergesort
void ordenaMergesort(int *v, int tamanho, int *mov, int *comp){
    int meio,i, *esquerda, *direita;
    if(tamanho < 2) return;

    meio = tamanho/2;
    esquerda = (int*)malloc(meio*sizeof(int));
    direita = (int*)malloc((tamanho - meio)*sizeof(int));

    for(i = 0;i<meio;i++) esquerda[i] = v[i];
    for(i = meio;i<tamanho;i++) direita[i-meio] = v[i];

    ordenaMergesort(esquerda,meio,mov,comp);
    ordenaMergesort(direita,tamanho-meio,mov,comp);
    merge(v,esquerda,meio,direita,tamanho-meio,mov,comp);
    free(esquerda);
    free(direita);
}

//ordena vetor por método inserção
int ordenaInsercao(vetor *v, int *comp){
    int j, i, x, mov = 0;
    for(j=1;j<v->tamanho;j++){
        mov++;
        x = v->v[j];
        i = j-1;
        while(i>=0 && v->v[i] > x){
            v->v[i+1] = v->v[i];
            i--;
            mov++;
            *comp = *comp + 1;
        }
        if(v->v[i+1] != x){
            mov++;
        }
        v->v[i+1] = x;

    }
}

//divide os vetores para ordenação de método quicksort
int separaQuick (vetor *v, int inicio, int final, int *mov, int *comp) {
   int c = v->v[inicio], i = inicio+1, j = final, t;
   while (i <= j) {
      *comp = *comp + 1;
      if (v->v[i] <= c){
          ++i;
      } else if (c < v->v[j]){
          --j;
      } else {
         t = v->v[i], v->v[i] = v->v[j], v->v[j] = t;
         ++i; --j;
         *mov = *mov + 3;
      }
   }
   v->v[inicio] = v->v[j], v->v[j] = c;
   *mov = *mov + 3;
   return j;
}

//ordena vetor por método quicksort
void ordenaQuicksort(vetor *v, int inicio, int final, int *mov, int *comp) {
   int j;
   while (inicio < final) {
      j = separaQuick(v, inicio, final, mov, comp);
      ordenaQuicksort(v, inicio, j-1, mov, comp);
      inicio = j + 1;
   }
}

//retorna o maior valor de um vetor
int retornaMax(int *v, int tamanho){
    int i, max;
    for(i=0;i<tamanho;i++){
        if(i==0){
            max = v[i];
        } else if(v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

//ordena vetor por método radixsort
int ordenaRadixsort(vetor *v) {
    int i, mov = 0, digito = 1, aux[v->tamanho], maior = retornaMax(v->v, v->tamanho);

    while (maior / digito > 0){
        int bucket[10] = { 0 };

        for (i = 0; i < v->tamanho; i++)
            bucket[(v->v[i] / digito) % 10]++;

        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];

        for (i = v->tamanho - 1; i >= 0; i--){
            aux[--bucket[(v->v[i] / digito) % 10]] = v->v[i];
            mov++;
        }

        for (i = 0; i < v->tamanho; i++){
            mov++;
            v->v[i] = aux[i];
        }

        digito *= 10;
    }
    return mov;
}

//adapta o vetor ao formato de heap
void reconstroiHeap(int *v, int limit, int pos, int *mov, int *comp) {
	int c1 = 2 * pos, c2;

	c2 = c1 + 1;

	if(c1 > limit || (v[pos - 1] >= v[c1 - 1] && v[pos - 1] >= v[c2 - 1])) {
		return;
    }

	int index = -1;

    *comp = *comp + 1;
	if(c2 > limit) {
		index = c1;
	} else {
        *comp = *comp + 1;
		if(v[c1 - 1] > v[c2 - 1]){
			index = c1;
		} else {
			index = c2;
        }
	}

    *mov = *mov + 3;
    if(index != -1) {
		int aux = v[index - 1];
		v[index - 1] = v[pos - 1];
		v[pos - 1] = aux;
		reconstroiHeap(v, limit, index, mov, comp);
	}
}

//adapta o vetor ao formato de heap
void transformaHeap(int *v, int size_v, int *mov, int *comp) {
	int left;

	if(size_v % 2 == 0) {
		left = size_v / 2 + 1;
	} else {
		left = (size_v - 1) / 2 + 1;
    }

	while(left > 1) {
		left--;
		reconstroiHeap(v, size_v, left, mov, comp);
	}
}

//ordena vetor por método heapsort
int ordenaHeapSort(vetor *v, int *comp) {
    int mov = 0;
	transformaHeap(v->v, v->tamanho, &mov, comp);
    int tamanho = v->tamanho;

    while(1) {
		int aux = v->v[0];
		v->v[0] = v->v[tamanho - 1];
		v->v[tamanho - 1] = aux;
        mov = mov + 3;

		reconstroiHeap(v->v, tamanho-- - 1, 1, &mov, comp);

		if(tamanho <= 2 && v->v[0] <= v->v[1]) {
			break;
        }
	}
}
