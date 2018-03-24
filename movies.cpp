#include <string.h>
#include <vector>
#include <stdlib.h>
#include "movies.h"

//retorna um filme da lista
Movie* getsMovie(std::vector<Movie*> ml, char id[10]){
  if(ml.size() == 0){
    return NULL;
  }

  std::vector<Movie*>::iterator it;

  for(it = ml.begin(); it != ml.end(); it++) {
    if((*it)->id == id){
      return *it;
    }
  }

  return NULL;
}

//adiciona um novo filme à lista
void addsMovie(std::vector<Movie*> ml, char id[10]){
  if(getsMovie(ml, id) == NULL){
    Movie *m = (Movie*)malloc(sizeof(Movie));
    strcpy(m->id, id);

    ml.push_back(m);
  }
}

//adiciona uma visualização à um filme
void addsView(Movie *m, char user[10], int rate){
  View *v = (View*)malloc(sizeof(View));

  strcpy(v->user, user);
  v->rate = rate;

  m->h.push_back(v);
}

//desaloca memória utilizada por uma lista de filmes
void freeMovies(std::vector<Movie*> ml){
  std::vector<Movie*>::iterator it;
  std::vector<View*>::iterator jt;

  for(it = ml.begin(); it != ml.end(); it++) {
    for(jt = (*it)->h.begin(); jt != (*it)->h.end(); jt++) {
      free(*jt);
    }
    free(*it);
  }
}
