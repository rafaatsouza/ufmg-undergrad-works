#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "movies.h"

using namespace std;

int main(int argc, char *argv[]){
  if(argc < 3){
    cout << "Error - Invalid arguments" << '\n';
    cout << "Error - Invalid arguments" << '\n';
    exit(EXIT_FAILURE);
  }

  MovieList movies;
  UserList users;

  GetRatings(argv[1], &movies, &users);
  SetPredictions(argv[2], &movies, &users);

  movies.clear();
  users.clear();

  return 0;
}
