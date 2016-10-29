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
    Mensagem *m = (Mensagem*)malloc(sizeof(Mensagem));

    m = t->topo;
    if(m->id_mensagem == id_mensagem){
        return m;
    } else {
        while(m->abaixo != NULL){
            if(m->id_mensagem == id_mensagem){
                return m;
            } else {
                m = m->abaixo;
            }
        }
    }
    return NULL;
}

void exibeTimeline(Usuario *us, int qtdUsuarios, Timeline *ts, int id_user, FILE *arq, int tempo){
    Usuario *u = retornaUsuario(us, qtdUsuarios, id_user);
    if(u != NULL){
        Timeline *t = retornaTimeline(ts, qtdUsuarios, id_user);
        if(t != NULL){
            int i;
            fprintf(arq, "%d %s\n", u->id, u->nome);

            Mensagem *m = (Mensagem*)malloc(sizeof(Mensagem));

            m = t->topo;
            while(m != NULL){
                fprintf(arq, "%d ", m->id_mensagem);
                for(i=0;i<(m->qtd_conteudo - 2);i++){
                    fprintf(arq, "%c", m->conteudo[i]);
                }
                fprintf(arq, " %d\n", m->qtd_curtidas);
                m = m->abaixo;
            }
        }
    }
}

int usuarioVeMsg(Amizade *a, Usuario *u, int id_autor){
    if(u->id == id_autor){
        return 1;
    }
    if(a->qtd <= 0){
        return 0;
    }
    Relacao *r = (Relacao*)malloc(sizeof(Relacao));

    r = a->primeira;
    while (r != NULL) {
        if((r->id1 == id_autor || r->id1 == u->id) && (r->id2 == id_autor || r->id2 == u->id)){
            return r->ativa;
        } else {
            r = r->prox;
        }
    }
    return 0;
}

void insereMensagem(Timeline *t, Amizade *a, Usuario *u, int qtdUsuarios, int id_mensagem, char *conteudo, int id_user, int tempo){
    int ti, i, qtd_conteudo = strlen(conteudo);

    if(qtd_conteudo > 140){
        qtd_conteudo = 140;
    }

    for(ti=0;ti<qtdUsuarios;ti++){
        Usuario *ut = retornaUsuario(u, qtdUsuarios, t[ti].id);
        if(usuarioVeMsg(a, ut, id_user) == 1){
            Mensagem *m = (Mensagem*)malloc(sizeof(Mensagem));

            m->id_mensagem = id_mensagem;
            m->id_usuario = id_user;
            m->tempo = tempo;
            m->abaixo = NULL;
            m->qtd_curtidas = 0;
            m->curtidas = NULL;
            m->qtd_conteudo = qtd_conteudo;
            m->conteudo = (char*)malloc(qtd_conteudo * sizeof(char));
            for(i = 0;i < qtd_conteudo; i++){
                if(conteudo[i] != '\n') {
                    m->conteudo[i] = conteudo[i];
                }
            }
            if(t[ti].qtd <= 0){
                t[ti].topo = m;
                t[ti].ultimo = m;
                t[ti].qtd = 1;
            } else {
                t[ti].ultimo->abaixo = m;
                m->acima = t[ti].ultimo;
                t[ti].ultimo = m;
                t[ti].qtd++;
            }
        }
    }
}

void reavaliaTimeline(Timeline *t, Mensagem *m){
    while(m->acima != NULL && m->qtd_curtidas >= m->acima->qtd_curtidas){
        Mensagem *m_de_cima, *m_aux;

        m_de_cima = m->acima;

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
            }
            m->abaixo = m_de_cima;
            if(m->abaixo != NULL){
                m_de_cima->abaixo = m_aux;
            } else {
                m_de_cima->abaixo = NULL;
                t->ultimo = m_de_cima;
            }

            t->topo = m;
            m->acima = NULL;
        }
    }
}

void curtirMensagem(Timeline *t, int qtdTimelines, int id_mensagem, int id_user, int tempo){
    int i;

    for(i=0;i<qtdTimelines;i++){
        Mensagem *m = retornaMensagem(&t[i], id_mensagem);
        if(m != NULL){
            Curtidas *c = (Curtidas*)malloc(sizeof(Curtidas));

            c->id_usuario = id_user;
            c->tempo = tempo;
            c->prox = NULL;

            if(m->qtd_curtidas <= 0){
                m->curtidas = c;
                m->qtd_curtidas = 1;
            } else {
                Curtidas *c_aux = (Curtidas*)malloc(sizeof(Curtidas));
                c_aux = m->curtidas->prox;
                while (c_aux != NULL) {
                    c_aux = c_aux->prox;
                }
                c_aux->prox = c;
                m->qtd_curtidas++;
            }
            reavaliaTimeline(&t[i], m);
        }
    }
}
