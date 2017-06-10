#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void OrdenaIndices(FILE *arquivo, char *diretorio, int qtdLinhas, int qtdMemoria){
    int i, qtdRestante, qtdMaxTamanho, qtdFitas, itensPorBloco, itensAtual = 0, filaAtual = 1, arq, freq, pos;
    FILE *fita;
    index **indices;
    char palavra[20], *NomFita;

    qtdMaxTamanho = 32;
    itensPorBloco = (qtdMemoria/qtdMaxTamanho);
    qtdFitas = 2*itensPorBloco;

    criaFitas(qtdFitas);
    printf(" ");

    qtdRestante = qtdLinhas;

    while(qtdRestante > 0){
        itensAtual = 0;
        arquivo = fopen(diretorio, "r");
        indices = (index**)malloc(sizeof(index*)*itensPorBloco);
        for(i=0;i<itensPorBloco && qtdRestante > 0;i++) { 
            fscanf(arquivo,"%s %d %d %d", palavra, &arq, &freq, &pos);
            indices[i] = defineIndex(palavra, arq, freq, pos);
            qtdRestante--;
            itensAtual++;
        }
        fclose(arquivo);

        indices = ordenaIndex(indices, itensPorBloco);

        sprintf(NomFita, "fita_%d.txt", filaAtual);
        fita = fopen(NomFita,"a");
        for(i=0;i<itensAtual;i++) { 
            fprintf(fita, "%s %d %d %d\n", indices[i]->palavra, indices[i]->arquivo, indices[i]->frequencia, indices[i]->posicao);
        }
        fclose(fita);
        for(i=0;i<itensAtual;i++) { 
            free(indices[i]);
        }
        free(indices);
        filaAtual++;
    }
}

int main(int argc, char *argv[]){
    int qtdDocumentos, qtdMemoria, contadorLetra, contadorPalavra, qtdLinhas = 0, i;

    char dirEntrada[255], dirSaida[255], nomArqSaida[255], nomArqLeitura[255], palavra[20], *buf;
    FILE *saida, *leitura;

    scanf("%d %d", &qtdDocumentos, &qtdMemoria);
    getchar();
    scanf(" %s", &dirEntrada);
    scanf(" %s\n", &dirSaida);
    
    sprintf(nomArqSaida, "%sindexx.txt", dirSaida);
    saida = fopen(nomArqSaida,"w");
    fclose(saida);
    saida = fopen(nomArqSaida,"a");

    for(i=1;i<=qtdDocumentos;i++){
        contadorLetra = 0;
        contadorPalavra = 1;
        sprintf(nomArqLeitura, "%s%d", dirEntrada, i);
        leitura = fopen(nomArqLeitura,"r");
        while(!feof(leitura)){
            fscanf(leitura,"%s",palavra);
            palavra[strlen(palavra)] = '\0';
            fprintf(saida, "%s %d %d %d\n", palavra, i, contadorPalavra, contadorLetra);
            qtdLinhas++;
            contadorLetra += strlen(palavra);
        }
        fclose(leitura);
    }
    fclose(saida);

    OrdenaIndices(saida, nomArqSaida, qtdLinhas, qtdMemoria);
}
