typedef struct u {
  int id;
  char *nome;
  int nome_qtd;
} Usuario;

void registraUsuario(Usuario *u, int id, char *n, int nome_qtd);
void listaInfoUsuario(Usuario *u);
