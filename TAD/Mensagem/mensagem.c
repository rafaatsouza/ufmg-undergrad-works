#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Amizade/amizade.h"
#include "../Usuario/usuario.h"
#include "mensagem.h"

void iniciaTimeline(int id_user, Timeline *t){
    t->qtd = 0;
    t->topo = NULL;
    t->id = id_user;
    t->ultimo = NULL;
}

Timeline* retornaTimeline(Timeline *t, int qtdTimelines, int id_user){
    int i;
    for(i=0;i<qtdTimelines;i++){
        if(t[i].id == id_user){
            return &t[i];
        }
    }
}

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

void insereMensagem(Timeline *t, Amizade *a, Usuario *u, int qtdUsuarios, int id_mensagem, char *conteudo, int id_user, int tempo, int tempo_exibicao){
    int ti, i;

    for(ti=0;ti<qtdUsuarios;ti++){
        Usuario *ut = retornaUsuario(u, qtdUsuarios, t[ti].id);
        if(usuarioVeMsg(a, ut->id, id_user) == 1 && retornaMensagem(&t[ti],id_mensagem) == NULL){
            Mensagem *m = (Mensagem*)malloc(sizeof(Mensagem));

            m->id_mensagem = id_mensagem;
            m->id_usuario = id_user;
            m->tempo = tempo;
            m->acima = NULL;
            m->abaixo = NULL;
            m->qtd_curtidas = 0;
            m->tempo_exibicao = tempo_exibicao;
            m->conteudo = (char*)malloc(strlen(conteudo) * sizeof(char));
            for(i = 0;i < strlen(conteudo) && i < 140; i++){
                if((int)(conteudo[i]) != 10 && (int)(conteudo[i]) != 13 && (int)(conteudo[i]) != 0) {
                    m->conteudo[i] = conteudo[i];
                }
            }
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

void reavaliaTimeline(Timeline *t, Mensagem *m){
    while(m->acima != NULL){
        Mensagem *m_de_cima = m->acima, *m_aux;

        if(m_de_cima->id_mensagem != t->topo->id_mensagem){
            m_de_cima->acima->abaixo = m;
            m->acima = m_de_cima->acima;
            m_de_cima->acima = m;
            if(m->abaixo != NULL){
                m_aux = m->abaixo;
                m_aux->acima = m_de_cima;
                m_de_cima->abaixo = m_aux;
            } else {
                m_de_cima->abaixo = NULL;
                t->ultimo = m_de_cima;
            }
            m->abaixo = m_de_cima;
        } else {
            m_de_cima->acima = m;
            if(m->abaixo != NULL){
                m_aux = m->abaixo;
                m_de_cima->abaixo = m_aux;
            } else {
                m_de_cima->abaixo = NULL;
                t->ultimo = m_de_cima;
            }
            m->abaixo = m_de_cima;
            t->topo = m;
            m->acima = NULL;
        }
    }
}

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
