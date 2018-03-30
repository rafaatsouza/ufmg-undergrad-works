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

  std::cout << "Quantidade de filmes: " << movies.size() << '\n';
  std::cout << "Quantidade de Usuários: " << users.size() << '\n';
  return 0;
}
