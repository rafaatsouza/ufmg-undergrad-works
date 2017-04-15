typedef struct v * t_prox;

typedef struct v {
  int val, iOperador;
  t_prox next;
} Value;

typedef struct {
  int count_numeros, count_operadores, resultado;
  t_prox first, last;
} filaNumeros;

void freeFila(filaNumeros *fn);
filaNumeros* createFV();
void addElement(filaNumeros *fn, int num, int iOperador);
