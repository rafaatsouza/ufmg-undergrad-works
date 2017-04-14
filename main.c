#include <stdio.h>
#include <string.h>
#include "TAD/filaNumeros.h"

int main(){
    int i = 0;
    char c;

    filaNumeros *fv = createFV();

    c = getchar();
    while(c != '\n' && c != '\0'){
        if(c != ' '){
            if(c != '?'){
                addElement(fv, (((int)c)-48), 0);
            } else {
                addElement(fv, 0, 1);
            }
        }
        c = getchar();
    }

    scanf("%d", &(fv->resultado));
    getchar();
    printResults(fv);

    free(fv);
    return 0;
}
