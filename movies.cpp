#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "movies.h"

using namespace std;

int getPrediction(string userId, string itemId, MovieList *movies, UserList *users){
  return 5;
}

void GetRatings(string filename, MovieList *movies, UserList *users){
  int count = 0;
  string::size_type size;
  ifstream file(filename.c_str());
  string line = "";

	while (getline(file, line)) {
    if(count > 0){
      string itemId;
      string userId;
      int rate;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      itemId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      userId = line.substr(0,dotsPosition);
      rate = stoi(line.substr(firstCommaPosition + 1, 1),&size);

      if((*movies).find(itemId) != (*movies).end()) {
        ((*movies)[itemId])[userId] = rate;
      } else {
        View vu;
        vu[userId] = rate;

        (*movies)[itemId] = vu;
      }

      if((*users).find(userId) != (*users).end()){
        ((*users)[userId])[itemId] = rate;
      } else {
        View vm;
        vm[itemId] = rate;

        (*users)[userId] = vm;
      }
    }

    count++;
  }
}

void SetPredictions(string filename, MovieList *movies, UserList *users){
  int count = 0;
  string::size_type size;
  ifstream file(filename.c_str());
  string line = "";

	while (getline(file, line)) {
    if(count > 0){
      string itemId;
      string userId;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      itemId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      userId = line.substr(0,dotsPosition);


      cout << line << "," << getPrediction(userId, itemId, movies, users) << '\n';
    } else {
      cout << "UserId:ItemId,Rating" << '\n';
    }
    count++;
  }
}
