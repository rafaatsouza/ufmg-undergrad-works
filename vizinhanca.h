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
void preencheVizinhanca(vizinhanca *v, int iDinamica);
void liberaVizinhanca(vizinhanca *v);
void dinamica(vizinhanca *v);
void guloso(vizinhanca *v);
void bruta(vizinhanca *v);
