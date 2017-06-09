#include <string.h>
#include "index.h"

index* defineIndex(char *pal, int arq, int freq, int pos){
	int j;
	index *i = (index*)malloc(sizeof(index));

	for(j=0;j<strlen(pal);j++){
		i->palavra[j] = pal[j];
	}
	i->palavra[j] = '\0';

	i->arquivo = arq;
	i->frequencia = freq;
	i->posicao = pos;

	return i;
}

index** ordenaIndex(index **indices, int qtdIndices){
	int i = (qtdIndices-1)/2, chave, k;
	index *aux;

    while(i != 0) {
        do {
            chave = 1;
            for(k = 0; k < qtdIndices - i; ++k) {
            	if(retornaMenor(indices[k], indices[k+1]) == 1) {
                    aux = indices[k];
                    indices[k] = indices[k+1];
                    indices[k+1] = aux;
                    chave = 0;
                }
            }
        } while(chave == 0);
        i = i / 2;
    }

	return indices;
}

//retorna 0 caso o indice_1 seja o menor, 1 caso o indice_2 seja o menor, e -1 caso sejam a mesma palavra
int retornaMenor(index *indice_1, index *indice_2){ 
	int caracter1, caracter2, compara = 0;

	while(compara < strlen(indice_1->palavra) && compara < strlen(indice_2->palavra)){
		caracter1 = (int)indice_1->palavra[compara];
		caracter2 = (int)indice_2->palavra[compara];

		if(caracter1 < caracter2){
			return 0;
		} else if(caracter1 > caracter2){
			return 1;
		} else {
			compara++;
		}
	}

	if(strlen(indice_1->palavra) < strlen(indice_2->palavra)){
		return 0;
	} else if(strlen(indice_1->palavra) < strlen(indice_2->palavra)){
		return 1;
	} else {
		return -1;
	}
}
