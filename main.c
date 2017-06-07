#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int qtdDocumentos, qtdMemoria, i;
    char dirEntrada[300], dirSaida[300], nomArqSaida[300], nomArqLeitura[300], *buf;
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
        buf = (char*)malloc(sizeof(char)*qtdMemoria);
        sprintf(nomArqLeitura, "%s%d", dirEntrada, i);
        leitura = fopen(nomArqLeitura,"r");
        while (fgets(buf,qtdMemoria,leitura) != NULL) {
            fprintf(saida, "%s\n", strtok(buf,""));
        }
        fclose(leitura);
    }
    fclose(saida);
}
