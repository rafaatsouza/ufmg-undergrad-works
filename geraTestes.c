#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc >= 3){
        int i, tamanho = atoi(argv[2]);
        char tipo;
        if(strcmp(argv[1],"d") == 0){
            tipo = 'd';
        } else if(strcmp(argv[1],"g") == 0){
            tipo = 'g';
        } else if(strcmp(argv[1],"b") == 0){
            tipo = 'b';
        } else {
            return 0;
        }

        printf("%c\n%d\n", tipo, tamanho);
        for(i=1;i<=tamanho*2;i = i + 2){
            printf("%d %d\n",i, i+1);
        }
    }
    return 0;
}
