#include <map>
#include <chrono>
#include <cstring>
#include <stdio.h>
#include "movies.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("Argumentos invalidos\n");
    exit(-1);
  }

  MovieList movies;
  UserList users;

  if(strcmp(argv[1],"-t") == 0){
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    GetRatings(argv[2], &movies, &users);
    SetPredictions(argv[3], &movies, &users);
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    printf("Duação %lf\n", ((double)duration_cast<microseconds>( fim - inicio ).count())/1000000);
  } else {
    GetRatings(argv[1], &movies, &users);
    SetPredictions(argv[2], &movies, &users);
  }

  movies.clear();
  users.clear();

  return 0;
}
