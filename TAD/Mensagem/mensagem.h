typedef struct p * tp_apont;

typedef struct c * tc_apont;

typedef struct c {
    int id_usuario, tempo;
    tc_apont prox;
} Curtidas;

typedef struct p {
  char *conteudo;
  int id_mensagem, qtd_conteudo, qtd_curtidas, id_usuario, tempo, tempo_exibicao;
  Curtidas *curtidas;
  tp_apont acima, abaixo;
} Mensagem;

typedef struct t {
    Mensagem *topo, *ultimo;
    int qtd, id;
} Timeline;

void iniciaTimeline(int id_user, Timeline *t);
void exibeTimeline(Usuario *us, int qtdUsuarios, Timeline *t, int id_user, FILE *arq, int tempo);
void insereMensagem(Timeline *t, Amizade *a, Usuario *u, int qtdUsuarios, int id_mensagem, char *conteudo, int id_user, int tempo, int tempo_exibicao);
void adicionaMensagens(Timeline *t, Amizade *a, Usuario *u, int qtdUsuarios, int id1, int id2, int tempo);
void curtirMensagem(Timeline *t, int qtdTimelines, int id_mensagem, int id_user, int tempo);
