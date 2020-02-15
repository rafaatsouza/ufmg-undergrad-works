typedef struct re {
    int indexPar, qtdRestricao;
} restricao;

typedef struct r {
    int bar, casa;
} relacao;

typedef struct v {
    relacao *r;
    int *par, *impar, qtdBar;
} vizinhanca;

vizinhanca* instanciaVizinhanca(int qtdBar);
void liberaVizinhanca(vizinhanca *v);
void dinamica(vizinhanca *v, int iIdentificaTipo);
void guloso(vizinhanca *v, int iIdentificaTipo);
void bruta(vizinhanca *v, int iIdentificaTipo);
