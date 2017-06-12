#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fitas.h"
#include "index.h"

void criaFitas(int qtdFitas){
    FILE *fita;
    int i;
    char *NomFita;

    for(i=0;i<qtdFitas;i++) {
        NomFita = (char*)malloc(sizeof(char)*255);
        sprintf(NomFita, "fita_%d.txt", i+1);
        fita = fopen(NomFita,"w");
        fclose(fita);
        free(NomFita);
    }
}

void deletaFitas(int qtdFitas){
    FILE *fita;
    int i;
    char *NomFita;

    for(i=0;i<qtdFitas;i++) {
        NomFita = (char*)malloc(sizeof(char)*255);
        sprintf(NomFita, "fita_%d.txt", i+1);
        remove(NomFita);
        free(NomFita);
    }
}

int preencheFitas(int qtdFitas, char *diretorio, int qtdLinhas, int itensPorBloco){
    int i, j, itensAtual = 0, fitaAtual = 1, arq, freq, pos, maxNumFita = 1;
    index **indices;
    FILE *fita, *arquivo;
    char palavra[20], NomFita[20];

    indices = (index**)malloc(sizeof(index*)*itensPorBloco);

    arquivo = fopen(diretorio, "r");
    for(i=0;i<qtdLinhas;i++){
        if(fscanf(arquivo,"%s %d %d %d\n", palavra, &arq, &freq, &pos) != -1){
            indices[itensAtual++] = defineIndex(palavra, arq, freq, pos);

            if(itensAtual > 0 && (i == qtdLinhas - 1 || itensAtual == itensPorBloco)){
                indices = ordenaIndex(indices, itensAtual);
                sprintf(NomFita, "fita_%d.txt", fitaAtual);
                fita = fopen(NomFita,"a");
                for(j=0;j<itensAtual;j++) {
                    fprintf(fita, "%s %d %d %d\n", indices[j]->palavra, indices[j]->arquivo, indices[j]->frequencia, indices[j]->posicao);
                    free(indices[j]);
                }
                fprintf(fita, "* \n");
                fclose(fita);
                free(indices);
                itensAtual = 0;
                fitaAtual++;
                if(fitaAtual > qtdFitas/2){ fitaAtual = 1; }
                if(fitaAtual > maxNumFita) { maxNumFita = fitaAtual; }
				if(i < qtdLinhas - 1 ){ indices = (index**)malloc(sizeof(index*)*itensPorBloco); }
            }
        }
    }
    fclose(arquivo);
    return maxNumFita;
}

void zeraFita(int numFita){
	FILE *fita;
	char NomFita[20];

	sprintf(NomFita, "fita_%d.txt", numFita);
	fita = fopen(NomFita,"w");
	fclose(fita);
}

void printaIndice(index *indice, int numFita){
	FILE *fita;
	char NomFita[20];

	sprintf(NomFita, "fita_%d.txt", numFita);
	fita = fopen(NomFita,"a");
	fprintf(fita, "%s %d %d %d\n", indice->palavra, indice->arquivo, indice->frequencia, indice->posicao);
	fclose(fita);
	free(indice);
}

int retornaLinhasLidas(int numLinhas, int qtd){
	if(numLinhas <= qtd){
		return numLinhas;
	} else {
		return numLinhas - (numLinhas/qtd);
	}
}

int PalavraEhIgual(char *palavra1, char *palavra2){
	int i;
	if(strlen(palavra1) != strlen(palavra2)){
		return 0;
	} else {
		for(i=0;i<strlen(palavra1);i++){
			if(palavra1[i] != palavra2[i]){
				return 0;
			}
		}
		return 1;
	}
}

void printaFinal(char *diretorio, int numFita){
	int arq, freq, pos, iMaisFreq = 0;
	FILE *saida, *fita;
	char ultimaPalavra[20], palavra[20], NomFita[20];

	ultimaPalavra[0] = "-";

	sprintf(NomFita, "fita_%d.txt", numFita);

	saida = fopen(diretorio,"w");
	fclose(saida);
	saida = fopen(diretorio,"a");

	fita = fopen(NomFita,"r");
	while(!feof(fita)){
		if(fscanf(fita,"%s %d %d %d\n", palavra, &arq, &freq, &pos) != -1){
			if(ultimaPalavra[0] != '-'){
				if(PalavraEhIgual(ultimaPalavra,palavra) == 1){
					iMaisFreq++;
				} else {
					iMaisFreq = 0;
				}
			}
			fprintf(saida, "%s,%d,%d,%d\n", palavra, arq, freq + iMaisFreq, pos);
			strcpy(ultimaPalavra,palavra);
		}
	}
	fclose(fita);
	fclose(saida);
}

void intercalaFitas(int qtdMaxMemoria, int qtdFitas, char *diretorio, int qtdLinhas, int itensPorBloco, int ultimaFitaPreenchida){
	int i, j, minFita = 1, itensNoIndice = 0, arq, freq, pos, min = -1, fitaAtual = ultimaFitaPreenchida+1, novoMin = -1, novoUltim, linhasEscritas = 0, *linhasLidas, *linhasEscritasPorFita;
	index **indices;
	FILE *fita;
	char palavra[20], NomFita[20];

	linhasLidas = (int*)malloc(sizeof(int)*qtdFitas);
	linhasEscritasPorFita = (int*)malloc(sizeof(int)*qtdFitas);

	for(i=0;i<qtdFitas;i++) {
		linhasLidas[i] = 0;
		linhasEscritasPorFita[i] = 0;
	}

    indices = (index**)malloc(sizeof(index*)*itensPorBloco);

	while(minFita != ultimaFitaPreenchida){
		itensPorBloco *= itensPorBloco;
		while(linhasEscritas < qtdLinhas){
			for(i=minFita;i<=ultimaFitaPreenchida && itensNoIndice < (qtdMaxMemoria/32);i++){
				if(min == -1 || (min == (i - minFita) && (retornaLinhasLidas(linhasLidas[i - minFita],(int)(sqrt(itensPorBloco))))%((int)(sqrt(itensPorBloco))) > 0)){
					int ultimaLinhaLida = linhasLidas[i - minFita];
					sprintf(NomFita, "fita_%d.txt", i);
					fita = fopen(NomFita,"r");
					//printf("vai ler até a posicao %d da fita %s \n", ultimaLinhaLida+1, NomFita);
					for(j=0;j<ultimaLinhaLida+1;j++){
						if(fscanf(fita,"%s ", palavra) != -1){
							if(palavra[0] != '*'){
								if(fscanf(fita,"%d %d %d\n", &arq, &freq, &pos) != -1 && j >= ultimaLinhaLida){
									//printf("leu ->>> %s %d %d %d\n", palavra, arq, freq, pos);
									if(min == -1){
										indices[itensNoIndice] = defineIndex(palavra, arq, freq, pos);
									} else {
										indices[min] = defineIndex(palavra, arq, freq, pos);
									}
									itensNoIndice++;
								}
								if(j >= linhasLidas[i - minFita]){
									linhasLidas[i - minFita] = linhasLidas[i - minFita] + 1;
								}
							}
						}
					}
					fclose(fita);
				}
			}
			if(itensNoIndice > 0){
				min = retornaIndexMenor(indices, qtdMaxMemoria/32);
				if(min >= 0){
					//printf("retira o menor, que eh a posicao %d -- qtd atual:%d\n", min, itensNoIndice);
					printaIndice(indices[min], fitaAtual);
					indices[min] = NULL;
					itensNoIndice--;
					linhasEscritasPorFita[fitaAtual]++;
					linhasEscritas++;
					if(novoMin == -1 || fitaAtual < novoMin){
						novoMin = fitaAtual;
					}
					if(linhasEscritasPorFita[fitaAtual] >= itensPorBloco){
						sprintf(NomFita, "fita_%d.txt", fitaAtual);
						fita = fopen(NomFita,"a");
						fprintf(fita, "*\n");
						fclose(fita);
						itensNoIndice = 0;
						novoUltim = ++fitaAtual;
						min = -1;
						for(i=0;i<qtdFitas;i++) { linhasLidas[i] = linhasLidas[i] + 1; }
						//printf("mudou de fita\n");
					}
				}
			}
		}
		for(i=minFita;i<=ultimaFitaPreenchida;i++){
			zeraFita(i);
		}
		for(i=0;i<=qtdFitas;i++){
			linhasLidas[i] = 0;
			linhasEscritasPorFita[i] = 0;
		}
		int aux = minFita;
		min = -1;
		itensNoIndice = 0;
		linhasEscritas = 0;
		minFita = novoMin;
		ultimaFitaPreenchida = fitaAtual;
		fitaAtual = aux;
		novoMin = -1;
		//printf("passou. min %d - max %d - atual %d\n", minFita, ultimaFitaPreenchida, fitaAtual);
	}
	printaFinal(diretorio,minFita);
}
