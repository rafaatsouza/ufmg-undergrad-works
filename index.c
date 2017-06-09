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
	return indices;
}