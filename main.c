//#include <time.h>
#include <stdio.h>
#include <string.h>
#include "TAD/filaElementos.h"
#include "Functions/possibilidades.h"

int main(){
    int num = 0, i = 0;
    char c;

    filaElementos *fv = createFV(); //cria uma fila vazia

    c = getchar();
    while(c != '\n' && c != '\0'){ //recebe os números e operadores da equação
        if(c == ' '){
            if(num > -1){
                addElement(fv, num, 0);
            }
            num = -1;
        } else if(c == '?') {
            addElement(fv, 0, 1);
            num = -1;
        } else {
            if(num == -1){
                num = (((int)c)-48);
            } else {
                num *= 10;
                num += (((int)c)-48);
            }
        }
        c = getchar();
    }

    scanf("%d", &(fv->resultado)); //recebe o resultado da equação
    getchar();
    // clock_t tempo_exec;
    // tempo_exec = clock();
    exibeResultados(fv); //chama método que calcula e exibe os resultados possiveis
    // tempo_exec = clock() - tempo_exec;
    // printf("Tempo gasto: %f segundos\n", ((double)tempo_exec)/CLOCKS_PER_SEC);
    freeFila(fv); //desaloca a memória referente à fila
    return 0;
}
