#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include "movies.h"

int main(int argc, char *argv[]){
  if(argc < 3){
    std::cout << "Error - Invalid arguments" << '\n';
    exit(EXIT_FAILURE);
  }

  char ratingsFileName[20];
  char targetsFileName[20];

  strcpy(ratingsFileName, argv[1]);
  strcpy(targetsFileName, argv[2]);

  std::cout << ratingsFileName << '\n';
  std::cout << targetsFileName << '\n';

  return 0;
}
