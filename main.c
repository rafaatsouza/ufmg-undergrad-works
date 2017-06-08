#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void OrdenaIndices(FILE *arquivo, char *diretorio, int qtdLinhas, int qtdMemoria){
    int i, qtdFitas = (qtdLinhas * 32)/qtdMemoria;
    
    if((qtdLinhas * 32)%qtdMemoria) { qtdFitas++; }

    qtdFitas++;

    printf("%d linhas, %d fitas\n", qtdLinhas, qtdFitas);
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
    //printf("%s\n", nomArqSaida);
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
            fprintf(saida, "%s,%d,%d,%d\n", palavra, i, contadorPalavra, contadorLetra);
            qtdLinhas++;
            contadorLetra += strlen(palavra);
        }
        fclose(leitura);
    }
    fclose(saida);

    OrdenaIndices(saida, nomArqSaida, qtdLinhas, qtdMemoria);
}
