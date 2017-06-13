#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fitas.h"

void CriaIndicesOrdenados(char *diretorio, int qtdLinhas, int qtdMemoria){
    int qtdMaxTamanho, qtdFitas, itensPorBloco, ultimaFitaPreenchida;

    qtdMaxTamanho = 32;
    itensPorBloco = (qtdMemoria/qtdMaxTamanho);
    qtdFitas = 2*itensPorBloco;

    criaFitas(qtdFitas);
    ultimaFitaPreenchida = preencheFitas(qtdFitas, diretorio, qtdLinhas, itensPorBloco);
    intercalaFitas(qtdMemoria,qtdFitas, diretorio, qtdLinhas, itensPorBloco, ultimaFitaPreenchida);
    deletaFitas(qtdFitas);
}

int main(int argc, char *argv[]){
    int i, qtdDocumentos, qtdMemoria, contadorLetra, contadorPalavra, qtdLinhas = 0;
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
            if(fscanf(leitura,"%s",palavra) != -1){
                palavra[strlen(palavra)] = '\0';
                fprintf(saida, "%s %d %d %d\n", palavra, i, contadorPalavra, contadorLetra);
                qtdLinhas++;
                contadorLetra += strlen(palavra) + 1;
            }
        }
        fclose(leitura);
    }
    fclose(saida);

    CriaIndicesOrdenados(nomArqSaida, qtdLinhas, qtdMemoria);
}
