#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <cstring>
#include <stdlib.h>
#include "movies.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]){
  if(argc < 3){
    cout << "Error - Invalid arguments" << '\n';
    cout << "Error - Invalid arguments" << '\n';
    exit(EXIT_FAILURE);
  }

  MovieList movies;
  UserList users;

  if(strcmp(argv[1],"-t") == 0){
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    GetRatings(argv[2], &movies, &users);
    SetPredictions(argv[3], &movies, &users);
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << "Duração: " << ((double)duration_cast<microseconds>( fim - inicio ).count())/1000000 << '\n';
  } else {
    GetRatings(argv[1], &movies, &users);
    SetPredictions(argv[2], &movies, &users);
  }

  movies.clear();
  users.clear();

  return 0;
}
