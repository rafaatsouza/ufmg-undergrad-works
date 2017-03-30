# TP 2 - AEDS 2

Trabalho prático que consiste em um módulo para testar ordenações de vetores, escolhendo o tipo de ordenação desejado, o grau de ordenação inicial e a quantidade de elementos à serem ordenados. Ao informar o tamanho do vetor, o tipo de ordenação, e o grau de ordenação inicial,  será  gerado  um  vetor  e  ordenado  conforme  escolhido,  sendo  exibido  ao  final  o tempo  gasto  para  a  operação  de  ordenação,  quantas  movimentações  e  comparações foram feitas.

#### Build
Makefile contém as instruções necessárias para gerar o executável (sistema Linux)

#### Instruções

Ao executar o programa, devem ser passados como parâmetros:

**1 - Tipo de ordenação:**

bol – BubbleSort

sel – Seleção

ins – Inserção

she – ShellSort

qui – QuickSort

hea – HeapSort

mer – MergeSort

rad – RadixSort

**2 - Quantidade de elementos**

**3 - Opções de grau de ordenação inicial:**

asc –  Vetor já totalmente ordenado.

desc – Vetor inversamente ordenado.

ale – Vetor com valores totalmente aleatorios.

qasc – Vetor com 90% dos valores crescentes, e 10% aleatórios.

**4 - "-P" caso queira queira que os vetores sejam exibidos na tela**

*Exemplo: "./tp2.out she 10 ale -P"
Onde "tp2.out" é o nome do executável, 

"she" é o identificador para o tipo de ordenação ShellSort, 

"10" é o número de elementos no vetor. 

"ale" informa que a ordenação inicial do vetor será totalmente aleatória,

"-P" informa que os vetores devem ser exibidos na tela.*
