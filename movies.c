#include <stdio.h>
#include <stdlib.h>
#include "movies.h"

//inicia uma nova lista de filmes
MovieList* initMovieList(){
  MovieList *ml = (MovieList*)malloc(sizeof(MovieList));
  ml->countMovies = 0;
  ml->primeiro = NULL;
  ml->ultimo = NULL;

  return ml;
}

//retorna um filme da lista
Movie* getsMovie(MovieList *ml, char id[10]){
  if(ml->countMovies == 0){
    return NULL;
  }

  Movie *m_aux = ml->primeiro;
  Movie *m_retorno = NULL;

  while (m_aux != NULL && m_retorno == NULL) {
    if(m_aux->id == id){
      m_retorno = m_aux;
    }
    m_aux = m_aux->prox;
  }
  free(m_aux);
  return m_retorno;
}

//adiciona um novo filme à lista
void addsMovie(MovieList *ml, char id[10]){
  if(getsMovie(ml, id) != NULL){
    Movie *m = (Movie*)malloc(sizeof(Movie));
    strcpy(m->id, id);
    m->prox = NULL;
    m->h = (History*)malloc(sizeof(History));
    m->h->countViews = 0;
    m->h->primeiro = NULL;
    m->h->ultimo = NULL;

    if(ml->countMovies > 0){
      ml->ultimo->prox = m;
      ml->ultimo = m;
    } else {
      ml->primeiro = m;
      ml->ultimo = m;
    }

    ml->countMovies++;
  }
}

//adiciona uma visualização à um filme
void addsView(Movie *m, char user[10], int rate){
  View *v = (View*)malloc(sizeof(View));

  strcpy(v->user, user);
  v->rate = rate;
  v->prox = NULL;

  if(m->h->countViews > 0){
    m->h->ultimo->prox = v;
    m->h->ultimo = v;
  } else {
    m->h->primeiro = v;
    m->h->ultimo = v;
  }

  m->h->countViews++;
}

//desaloca memória utilizada por uma lista de filmes
void freeMovies(MovieList *ml){
  if(ml->countMovies > 0){
    Movie *m = ml->primeiro;
    Movie *aux;

    while (m != NULL) {
      aux = m;
      m = m->prox;
      freeMovie(aux);
    }
  }
  free(ml);
}

//desaloca memória utilizada por um filmes
void freeMovie(Movie *m){
  if(m->h->countViews > 0){
    View *v = m->h->primeiro;
    View *aux;

    while (v != NULL) {
      aux = v;
      v = v->prox;
      freeMovie(aux);
    }
  }

  free(m->h);
  free(m);
}
