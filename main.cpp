#include <iostream>
#include <fstream>
#include <string>
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
  char *content, *identifier, *prediction, *itemId, *userId;

  FILE* stream = fopen(argv[1], "r"); //argv[1] = ratingsFileName
  while (fgets(line, 1024, stream))
  {
      if (line[0] != '\n' && line[0] != ' '){
        content = strtok(line,"");
        
        identifier = strtok(content,",");
        prediction = strtok(NULL,",");

        userId = strtok(identifier,":");
        itemId = strtok(NULL,":");

        std::cout << "Usuario " << userId << " - Item " << itemId << " - Prediction " << prediction << '\n';
      }
  }

  return 0;
}
