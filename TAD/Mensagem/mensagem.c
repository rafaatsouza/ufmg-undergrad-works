#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Amizade/amizade.h"
#include "../Usuario/usuario.h"
#include "mensagem.h"

//inicia uma nova timeline para um usuario
void iniciaTimeline(int id_user, Timeline *t){
    t->qtd = 0;
    t->topo = NULL;
    t->id = id_user;
    t->ultimo = NULL;
}

//retorna o end. de memória da timeline de um usuario
Timeline* retornaTimeline(Timeline *t, int qtdTimelines, int id_user){
    int i;
    for(i=0;i<qtdTimelines;i++){
        if(t[i].id == id_user){
            return &t[i];
        }
    }
}

//retorna o end. de memória de uma mensagem em uma timeline específica
Mensagem* retornaMensagem(Timeline *t, int id_mensagem){
    if(t->qtd == 0){
        return NULL;
    }

    Mensagem *m = t->topo;
    while(m != NULL){
        if(m->id_mensagem == id_mensagem){
            return m;
        } else {
            m = m->abaixo;
        }
    }
    return NULL;
}

//imprime a timeline de um usuario no arquivo especificado
void exibeTimeline(Usuario *us, int qtdUsuarios, Timeline *ts, int id_user, FILE *arq, int tempo){
    Usuario *u = retornaUsuario(us, qtdUsuarios, id_user);
    if(u != NULL){
        Timeline *t = retornaTimeline(ts, qtdUsuarios, id_user);
        if(t != NULL){
            fprintf(arq, "%d %s\n", u->id, u->nome);
            if(t->qtd > 0){
                int i;
                Mensagem *m = t->topo;
                while(m != NULL){
                    if(m->tempo_exibicao == -1){
                        fprintf(arq, "%d %s %d\n", m->id_mensagem, m->conteudo, m->qtd_curtidas);
                        m->tempo_exibicao = tempo;
                    }
                    m = m->abaixo;
                }
                free(m);
            }
        }
    }
}

//retorna se usuario pode ver a mensagem de um determinado autor
int usuarioVeMsg(Amizade *a, int id1, int id_autor){
    if(id1 == id_autor){
        return 1;
    }
    if(a->qtd <= 0){
        return 0;
    }
    Relacao *r = a->primeira;
    while (r != NULL) {
        if((r->id1 == id_autor || r->id1 == id1) && (r->id2 == id_autor || r->id2 == id1)){
            return r->ativa;
        } else {
            r = r->prox;
        }
    }
    free(r);
    return 0;
}

//método para checar e adaptar a string de conteudo para ser armazenada na variável de mensagem
void AdaptaConteudo(char *m){
    int i, length = 0;

    for(i = 0;i <= strlen(m); i++){
        if((int)(m[i]) != 10 && (int)(m[i]) != 13 && (int)(m[i]) != 0 && (int)(m[i]) != 9) {
            length++;
        }
    }

    if(length > 0){
        char *retorno = (char*)malloc((length - 1) * sizeof(char));
        int j = 0;
        for(i = 0;i <= (length - 1); i++){
            if((int)(m[i]) != 10 && (int)(m[i]) != 13 && (int)(m[i]) != 0 && (int)(m[i]) != 9) {
                retorno[j] = m[i];
                j++;
            } else {
                length++;
            }
        }
        strcpy(m,retorno);
        free(retorno);
    }
}

//cria uma mensagem em todas as timelines de usuarios que podem ver essa mensagem
void insereMensagem(Timeline *t, Amizade *a, Usuario *u, int qtdUsuarios, int id_mensagem, char *conteudo, int id_user, int tempo, int tempo_exibicao){
    int ti, i;

    AdaptaConteudo(conteudo);

    for(ti=0;ti<qtdUsuarios;ti++){
        Usuario *ut = retornaUsuario(u, qtdUsuarios, t[ti].id);
        if(usuarioVeMsg(a, ut->id, id_user) == 1 && retornaMensagem(&t[ti],id_mensagem) == NULL){
            Mensagem *m = (Mensagem*)malloc(sizeof(Mensagem));
            int max_conteudo = 140;

            m->id_mensagem = id_mensagem;
            m->id_usuario = id_user;
            m->tempo = tempo;
            m->acima = NULL;
            m->abaixo = NULL;
            m->qtd_curtidas = 0;
            m->tempo_exibicao = tempo_exibicao;
            m->conteudo = (char*)malloc(strlen(conteudo) * sizeof(char));
            strcpy(m->conteudo, conteudo);
            if(t[ti].qtd <= 0){
                t[ti].topo = m;
                t[ti].ultimo = m;
                t[ti].qtd = 1;
            } else {
                m->abaixo = t[ti].topo;
                t[ti].topo->acima = m;
                t[ti].topo = m;
                t[ti].qtd++;
            }
        }
    }
}

//"sobe" uma mensagem para o topo da timeline
void reavaliaTimeline(Timeline *t, Mensagem *m){
    if(m->id_mensagem != t->topo->id_mensagem){
        if(m->acima->id_mensagem == t->topo->id_mensagem){
            t->topo->acima = m;
            if(m->abaixo != NULL){
                t->topo->abaixo = m->abaixo;
            } else {
                t->topo->abaixo = NULL;
                t->ultimo = t->topo;
            }
        } else {
            if(m->abaixo != NULL){
                m->acima->abaixo = m->abaixo;
                m->abaixo->acima = m->acima;
            } else {
                m->acima->abaixo = NULL;
                t->ultimo = m->acima;
            }
            t->topo->acima = m;
        }
        m->abaixo = t->topo;
        t->topo = m;
        m->acima = NULL;
    }
}

//adiciona as mensagens de autoria dos dois usuarios na timeline de cada um deles
void adicionaMensagens(Timeline *t, Amizade *a, Usuario *u, int qtdUsuarios, int id1, int id2, int tempo){
    int i, ti;
    for(ti=0;ti<qtdUsuarios;ti++){
        if(t[ti].qtd > 0 && (t[ti].id == id1 || t[ti].id == id2)){
            Mensagem *m = t[ti].topo;
            while(m != NULL){
                if(m->id_usuario == t[ti].id){
                    insereMensagem(t, a, u, qtdUsuarios, m->id_mensagem, m->conteudo, m->id_usuario, tempo, tempo);
                }
                m = m->abaixo;
            }
            free(m);
        }
    }
}

//curte uma mensagem em todas as timelines que ela esteja presente
void curtirMensagem(Timeline *t, int qtdTimelines, int id_mensagem, int id_user, int tempo){
    int i;

    for(i=0;i<qtdTimelines;i++){
        Mensagem *m = retornaMensagem(&t[i], id_mensagem);
        if(m != NULL){
            if(m->qtd_curtidas <= 0){
                m->qtd_curtidas = 1;
            } else {
                m->qtd_curtidas++;
            }
            m->tempo_exibicao = -1;
            reavaliaTimeline(&t[i], m);
        }
    }
}
