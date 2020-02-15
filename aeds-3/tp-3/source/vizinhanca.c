#include <stdio.h>
#include <stdlib.h>
#include "vizinhanca.h"

void converteParaDecimal(int num, char *possibilidade, int qtd){
    int j, i = qtd-1, resto;
    while(num >= 1){
        resto = num % 2;
        num = (num-resto)/2;
        if(resto == 0){
            possibilidade[i] = '0';
        } else {
            possibilidade[i] = '1';
        }
        i--;
        if(num == 1){
            possibilidade[i] = '1';
            i--;
            break;
        }
    }
    for(j=i;j>=0;j--){
        possibilidade[j] = '0';
    }
}

int retornaMax(int *v, int tamanho){
    int i, max;
    for(i=0;i<tamanho;i++){
        if(i==0){
            max = v[i];
        } else if(v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

void ordenaRadixsort(int *v, int tamanho) {
    int i, digito = 1, aux[tamanho], maior = retornaMax(v, tamanho);

    while (maior / digito > 0){
        int bucket[10] = { 0 };
        for (i = 0; i < tamanho; i++) { bucket[(v[i] / digito) % 10]++; }
        for (i = 1; i < 10; i++) { bucket[i] += bucket[i - 1]; }
        for (i = tamanho - 1; i >= 0; i--){ aux[--bucket[(v[i] / digito) % 10]] = v[i]; }
        for (i = 0; i < tamanho; i++){ v[i] = aux[i]; }
        digito *= 10;
    }
}

vizinhanca* instanciaVizinhanca(int qtdBar){
    vizinhanca *v = (vizinhanca*)malloc(sizeof(vizinhanca));

    v->qtdBar = qtdBar;
    v->r = (relacao*)malloc(sizeof(relacao) * qtdBar);
    v->par = (int*)malloc(sizeof(int) * qtdBar);
    v->impar = (int*)malloc(sizeof(int) * qtdBar);

    return v;
}

void liberaVizinhanca(vizinhanca *v){
    free(v->par);
    free(v->impar);
    free(v->r);
    free(v);
}

void ordenaDinamica(vizinhanca *v){
    int chave, k, aux, i = (v->qtdBar - 1) / 2;

    while(i != 0) {
        do {
            chave = 1;
            for(k = 0; k < v->qtdBar - i; ++k) {
                if(v->par[k] > v->par[k + i]) {
                    aux = v->par[k];
                    v->par[k] = v->par[k + i];
                    v->par[k + i] = aux;

                    aux = v->impar[k];
                    v->impar[k] = v->impar[k + i];
                    v->impar[k + i] = aux;
                    chave = 0;
                }
            }
        } while(chave == 0);
        i = i / 2;
    }
}

void preencheVizinhanca(vizinhanca *v, int iDinamica){
    int i, bar, casa;

    for(i=0;i<v->qtdBar;i++){
        scanf("%d %d", &bar, &casa);
        v->r[i].bar = bar;
        v->r[i].casa = casa;
        if(bar%2 == 0){
            v->par[i] = bar;
            v->impar[i] = casa;
        } else {
            v->par[i] = casa;
            v->impar[i] = bar;
        }
    }

    if(iDinamica){
        ordenaDinamica(v);
    } else {
        ordenaRadixsort(v->par, v->qtdBar);
        ordenaRadixsort(v->impar, v->qtdBar);
    }
}

int retornaCorrespondenteImpar(vizinhanca *v, int par){
    int i, impar = -1;
    for(i=0;i<v->qtdBar && impar == -1;i++){
        if(v->r[i].bar == par){
            impar = v->r[i].casa;
        } else if(v->r[i].casa == par){
            impar = v->r[i].bar;
        }
    }
    for(i=0;i<v->qtdBar;i++){
        if(v->impar[i] == impar){
            return i;
        }
    }
    return -1;
}

int SolucaoEhInvalida(vizinhanca *v, int *solucao){
    int i, j, indexPar, indexImpar, auxIndexPar, auxIndexImpar;

    for(i=0;i<v->qtdBar;i++){
        if(solucao[i] != -1){
            indexImpar = retornaCorrespondenteImpar(v, v->par[i]);
            indexPar = i;
            for(j=0;j<v->qtdBar;j++){
                if(j != i && solucao[j] != -1){
                    auxIndexImpar = retornaCorrespondenteImpar(v, v->par[j]);
                    auxIndexPar = j;

                    if((auxIndexPar < indexPar && auxIndexImpar > indexImpar) || (auxIndexPar > indexPar && auxIndexImpar < indexImpar)){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

restricao* montaRestricoes(vizinhanca *v){
    int indexImpar, auxIndexImpar, i, j;
    restricao *re = (restricao*)calloc(v->qtdBar, sizeof(restricao));

    for(i=0;i<v->qtdBar;i++){
        re[i].indexPar = i;
        re[i].qtdRestricao = 0;
        indexImpar = retornaCorrespondenteImpar(v, v->par[i]);
        for(j=0;j<v->qtdBar;j++){
            if(j != i){
                auxIndexImpar = retornaCorrespondenteImpar(v, v->par[j]);
                if((j > i && auxIndexImpar < indexImpar) || (j < i && auxIndexImpar > indexImpar)){
                    re[i].qtdRestricao = re[i].qtdRestricao + 1;
                }
            }
        }
    }

    return re;
}

void guloso(vizinhanca *v, int iIdentificaTipo){
    int i, j, count = 0, aux;
    int *possibilidade;
    restricao *restricoes;

    preencheVizinhanca(v, 0);
    restricoes = montaRestricoes(v);
    possibilidade = (int*)malloc(sizeof(int) * v->qtdBar);

    for(i=0;i<v->qtdBar;i++){ possibilidade[i] = -1; }

    for(i=0;i < v->qtdBar;i++){
        aux = -1;
        for(j=0;j<v->qtdBar;j++){
            if(restricoes[j].indexPar >= 0 && (aux == -1 || restricoes[aux].qtdRestricao >= restricoes[j].qtdRestricao)){
                aux = j;
            }
        }
        possibilidade[aux] = 1;
        if(SolucaoEhInvalida(v, possibilidade) == 1){
            possibilidade[aux] = -1;
        } else {
            count++;
        }
        restricoes[aux].indexPar = -1;
    }

    if(iIdentificaTipo == 1){
        printf("Metodo: Guloso - Quantidade: %d - ", v->qtdBar);
    }
    printf("%d\n", count);
    free(restricoes);
    free(possibilidade);
}

void bruta(vizinhanca *v, int iIdentificaTipo){
    int *possibilidadeAtual, maxBandeirolas = 0, count, i, j;
    long long int aux = ((pow(2,v->qtdBar)) - 1);
    char *possibilidade;

    possibilidade = (char*)malloc(sizeof(char) * v->qtdBar);
    possibilidadeAtual = (int*)malloc(sizeof(int) * v->qtdBar);

    preencheVizinhanca(v, 0);

    while(aux >= 0){
        count = 0;
        converteParaDecimal(aux, possibilidade, v->qtdBar);
        for(i=0;i<v->qtdBar;i++){
            if(possibilidade[i] == '1'){
                possibilidadeAtual[i] = v->par[i];
                count++;
            } else {
                possibilidadeAtual[i] = -1;
            }
        }
        if(count > maxBandeirolas){
            if(SolucaoEhInvalida(v, possibilidadeAtual) == 0){
                maxBandeirolas = count;
            }
        }
        aux--;
    }

    free(possibilidade);
    free(possibilidadeAtual);

    if(iIdentificaTipo == 1){
        printf("Metodo: Forca Bruta - Quantidade: %d - ", v->qtdBar);
    }
    printf("%d\n", maxBandeirolas);
}

void dinamica(vizinhanca *v, int iIdentificaTipo){
    int i, j;
    int *sequencias;

    sequencias = (int*)malloc(sizeof(int) * v->qtdBar);
    sequencias[0] = 1;

    preencheVizinhanca(v, 1);

    for(i=1;i<v->qtdBar;i++) {
        sequencias[i] = 1;
        for(j=0;j<i;j++) {
            if (v->impar[j] < v->impar[i] && sequencias[i] <= sequencias[j]) {
                sequencias[i] = sequencias[j] + 1;
            }
        }
    }

    if(iIdentificaTipo == 1){
        printf("Metodo: Prog. Dinamica - Quantidade: %d - ", v->qtdBar);
    }
    printf("%d\n", retornaMax(sequencias, v->qtdBar));

    free(sequencias);
}
