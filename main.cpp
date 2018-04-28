#include <map>
#include <chrono>
#include <cstring>
#include <stdio.h>
#include "movies.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]){
  if(argc < 4){
    printf("Argumentos invalidos\n");
    exit(-1);
  }
  
  MovieList movies;
  UserList users;

  if(strcmp(argv[1],"-t") == 0){
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    GetMoviesInfo(argv[3], &movies, &users);
    SetPredictions(argv[4], &movies, &users);
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    printf("Duração %lf\n", ((double)duration_cast<microseconds>( fim - inicio ).count())/1000000);
  } else {
    GetMoviesInfo(argv[2], &movies, &users);
    SetPredictions(argv[3], &movies, &users);
  }

  movies.clear();
  users.clear();

  return 0;
}
