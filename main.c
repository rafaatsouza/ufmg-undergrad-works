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

void preencheFitas(int qtdFitas, char *diretorio, int qtdLinhas, int itensPorBloco){
    int i, j, itensAtual = 0, fitaAtual = 1, arq, freq, pos;
    index **indices;
    FILE *fita, *arquivo;
    char palavra[20], NomFita[15];

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
                fprintf(fita, "\n");
                fclose(fita);
                free(indices);
                itensAtual = 0;
                fitaAtual++;
                if(fitaAtual > qtdFitas/2){ fitaAtual = 1; }
                indices = (index**)malloc(sizeof(index*)*itensPorBloco);
            }
        }
    }
    fclose(arquivo);
}

void CriaIndicesOrdenados(char *diretorio, int qtdLinhas, int qtdMemoria){
    int qtdMaxTamanho, qtdFitas, itensPorBloco;

    qtdMaxTamanho = 32;
    itensPorBloco = (qtdMemoria/qtdMaxTamanho);
    qtdFitas = 2*itensPorBloco;

    criaFitas(qtdFitas);
    preencheFitas(qtdFitas, diretorio, qtdLinhas, itensPorBloco);
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

    CriaIndicesOrdenados(nomArqSaida, qtdLinhas, qtdMemoria);
}
