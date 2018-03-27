#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "movies.h"

int main(int argc, char *argv[]){
  if(argc < 3){
    std::cout << "Error - Invalid arguments" << '\n';
    exit(EXIT_FAILURE);
  }

  char line[1024];
  char* content;

  FILE* stream = fopen(argv[1], "r"); //ratingsFileName
  while (fgets(line, 1024, stream))
    {
        if (line[0] != '\n' && line[0] != ' '){
          content = strtok(line,"");
          printf("%s\n", content);
        }
    }
    
  //std::cout << "ID: " << movieList.size() << '\n';

  return 0;
}
