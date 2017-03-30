# TP Allegro - AEDS 1

Trabalho prático com finalidade de simular o jogo "Bomberman" usando a linguagem de programação C com a biblioteca Allegro.

#### Build
Makefile contém as instruções necessárias para gerar o executável (sistema Linux).

#### Instruções
O objetivo do jogo é matar os inimigos (de vermelho) na tela usando as bombas, colocadas no jogo controlando o bomberman(de azul). Ao iniciar o jogo, as posições do bomberman e a dos três inimigos são definidas aleatoriamente, tendo como critér
ios: Nenhum elemento (inimigo ou bomberman) estar na mesma localização, ou em uma distância menor que 100 de outro 
elemento. Nos primeiros 2 segundos de todas as fases, o bomberman possui invencibilidade. 
###### Os comandos do teclado são:
W, S, A, D: Movem o bomberman para cima, baixo, esquerda e direita, respectivamente.
Espaço: Solta uma bomba na localização que o bomberman está. A bomba explode 1 segundo após ser colocada, e tem um raio igual à 64 (o dobro do “lado” do bomberman e dos inimigos, que tem tamanho 32x32). Ao explodir, são mortos todos os inimigos no raio, e o bomberman também, caso esteja no raio da bomba.Ao matar todos os inimigos, os três inimigos são recriados novamente em posições aleátorias com os mesmos critérios do inicio do jogo, mas com velocidade maior (a velocidade é acrescida sempre ao passar de fase).

Caso o bomberman seja alcançado por um inimigo ou esteja no raio de uma bomba no momento de explosão, ele morre e a tela mostra a pontuação. 
###### Critérios de pontuação:
Matar inimigo: 10 pontos + valor variável (cresce ao passar de fase).

Morrer para uma bomba: -[10 pontos + valor variável (cresce ao passar de fase)].

Tempo: 1 ponto por segundo * valor variável (cresce ao passar de fase). Observação: só é contado à partir da 2º fase.
