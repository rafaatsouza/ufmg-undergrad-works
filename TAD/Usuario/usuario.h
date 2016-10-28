typedef struct u {
  int id;
  char *nome;
  int nome_qtd;
} Usuario;

void registraUsuario(Usuario *u, int id, char *n, int nome_qtd);
Usuario* retornaUsuario(Usuario *u, int qtdUsuarios, int id_user);
