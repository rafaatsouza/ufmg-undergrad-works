typedef struct u {
  int id;
  char *nome;
} Usuario;

void registraUsuario(Usuario *u, int id, char *n);
Usuario* retornaUsuario(Usuario *u, int qtdUsuarios, int id_user);
