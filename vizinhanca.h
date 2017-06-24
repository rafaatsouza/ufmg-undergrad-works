typedef struct r {
    int bar, casa;
} relacao;

typedef struct v {
    relacao *r;
    int *bares, *casas, qtdBar;
} vizinhanca;

vizinhanca* instanciaVizinhanca(int qtdBar);
void preencheVizinhanca(vizinhanca *v);
void dinamica(vizinhanca *v);
void guloso(vizinhanca *v);
void bruta(vizinhanca *v);
