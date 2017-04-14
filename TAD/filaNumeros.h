typedef struct v * t_prox;

typedef struct v {
  int val, iOperador;
  t_prox next, ant;
} Value;

typedef struct {
  int count_numeros, resultado;
  t_prox first, last;
} filaNumeros;

filaNumeros* createFV();
void addElement(filaNumeros *pv, int num, int iOperador);
void imprimeFila(filaNumeros* fv);
