typedef struct i {
	char palavra[20];
	int arquivo, frequencia, posicao;
} index;

index* defineIndex(char* palavra, int arq, int freq, int pos);
index** ordenaIndex(index **indices, int qtdIndices);