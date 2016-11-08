#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TAD/Amizade/amizade.h"
#include "TAD/Usuario/usuario.h"
#include "TAD/Mensagem/mensagem.h"

//retorna o numero de caracteres ";" na string
int retornaQtdDelimiter(char *s){
  int qtd = 0;
  while((s = strchr(s, ';')) != NULL) {
      qtd++;
      s++;
  }
  return qtd;
}

int main(){
  FILE *entrada, *saida;
  int contador_entrada = 1;
  char arquivo_entrada[100] = "entrada01.txt", arquivo_saida[100] = "log.entrada01.txt";

  //abre cada arquivo de entrada possivel
  while((entrada = fopen(arquivo_entrada,"r")) != NULL){
      int i = 0, j = 0, qtdUsuarios;
      //iinicializa as variaveis e abre os arquivos
      saida = fopen(arquivo_saida,"w");
      fclose(saida);
      saida = fopen(arquivo_saida,"a");
      fscanf(entrada,"%d", &qtdUsuarios);
      Usuario *usuarios = (Usuario*)malloc(qtdUsuarios * sizeof(Usuario)), *user_executa;
      Timeline *timeline = (Timeline*)malloc(qtdUsuarios * sizeof(Timeline));
      Amizade *amizades = iniciaListaAmizade();
      char *nome, *content, buf[1000];
      int id, quantidade_amizades, tempo, codigo_acao, id_mensagem, novo_amigo;
      //lê cada linha do arquivo atual
      while (fgets(buf,1000,entrada) != NULL) {
        if (buf[0] != '\n' && buf[0] != ' ' && buf[0] != ""){
          content = strtok(buf,"");
          if(retornaQtdDelimiter(content)> 0){
            if(i < qtdUsuarios){
                quantidade_amizades = retornaQtdDelimiter(content) - 1;
                id = atoi(strtok(content,";"));
                nome = strtok(NULL,";");
                registraUsuario(&usuarios[i],id,nome); //chama funcao para registrar usuario
                iniciaTimeline(id, &timeline[i]); //cria uma timeline para o novo usuario
                //cria as amizades do novo usuario
                for(j=0;j<quantidade_amizades;j++){
                  iniciarAmizade(amizades, id, atoi(strtok(NULL,";")),0);
                }
                i++;
            } else {
                tempo = atoi(strtok(content,";"));
                codigo_acao = atoi(strtok(NULL,";"));
                user_executa = retornaUsuario(usuarios, qtdUsuarios, atoi(strtok(NULL,";")));
                //verifica qual a ação, e chama a função correspondente
                if(user_executa != NULL){
                    switch(codigo_acao){
                        case 1:
                            id_mensagem = atoi(strtok(NULL,";"));
                            insereMensagem(timeline, amizades, usuarios, qtdUsuarios, id_mensagem, strtok(NULL,";"), user_executa->id, tempo, -1);
                        break;
                        case 2:
                            novo_amigo = atoi(strtok(NULL,";"));
                            iniciarAmizade(amizades, user_executa->id, novo_amigo,tempo);
                            adicionaMensagens(timeline, amizades, usuarios, qtdUsuarios, user_executa->id, novo_amigo, tempo);
                        break;
                        case 3:
                            cancelarAmizade(amizades, user_executa->id, atoi(strtok(NULL,";")),tempo);
                        break;
                        case 4:
                            curtirMensagem(timeline, qtdUsuarios, atoi(strtok(NULL,";")), user_executa->id, tempo);
                        break;
                        case 5:
                            exibeTimeline(usuarios, qtdUsuarios, timeline, user_executa->id, saida, tempo);
                        break;
                    }
                }
            }
          }
        }
      }
      //fecha os arquivos e libera as memórias alocadas
      fclose(saida);
      fclose(entrada);
      for(i=0;i<qtdUsuarios;i++){
          free(usuarios[i].nome);
      }
      free(usuarios);
      Mensagem *m_aux, *m = timeline->topo;
      while(m != NULL){
          m_aux = m;
          m = m->abaixo;
          free(m_aux);
      }
      free(m);
      free(timeline);
      Relacao *r_aux, *r = amizades->primeira;
      while (r != NULL) {
        r_aux = r;
        r = r->prox;
        free(r_aux);
      }
      free(r);
      free(amizades);
      //muda o nome dos arquivos
      contador_entrada++;
      if(contador_entrada > 9){
          sprintf(arquivo_saida, "log.entrada%d.txt", contador_entrada);
          sprintf(arquivo_entrada, "entrada%d.txt", contador_entrada);
      } else {
          sprintf(arquivo_saida, "log.entrada0%d.txt", contador_entrada);
          sprintf(arquivo_entrada, "entrada0%d.txt", contador_entrada);
      }
  }
  return 0;
}
