typedef struct {
    char *result;
    int valid;
    filaNumeros *fn;
} possibilidadeResult;

void criaPossibilidades(possibilidadeResult *pr, int count);
void retornaPossibilidades(possibilidadeResult *pr, int count);
void printResults(filaNumeros *fn);