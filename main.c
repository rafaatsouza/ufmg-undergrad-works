#include <stdio.h>
#include <string.h>
#include "TAD/filaElementos.h"
#include "Functions/possibilidades.h"

int main(){
    int num = 0, i = 0;
    char c;

    filaElementos *fv = createFV();

    c = getchar();
    while(c != '\n' && c != '\0'){
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

    scanf("%d", &(fv->resultado));
    getchar();
    exibeResultados(fv);
    freeFila(fv);
    return 0;
}
