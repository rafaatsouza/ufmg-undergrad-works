typedef struct v * t_prox;

typedef struct v {
  int val, iOperador;
  t_prox next;
} Value;

typedef struct {
  int count_numeros, count_operadores, resultado;
  t_prox first, last;
} filaElementos;

void freeFila(filaElementos *fn);
filaElementos* createFV();
void addElement(filaElementos *fn, int num, int iOperador);
