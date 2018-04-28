#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <math.h>
#include "movies.h"

using namespace std;

double _totalAverage;

double GetPrediction(){
  return _totalAverage;
}

void SetPredictions(string filename, MovieList *movies, UserList *users){
  int count = 0;
  string::size_type size;
  ifstream file(filename.c_str());
  string line = "";

	while (getline(file, line)) {
    if(count > 0){
      string movieId;
      string userId;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      movieId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      userId = line.substr(0,dotsPosition);


      cout << line << "," << GetPrediction() << '\n';
    } else if(count == 0) {
      cout << "UserId:ItemId,Prediction" << '\n';
    }
    count++;
  }

  file.close();
}

void GetMoviesInfo(string ratingsFileName, MovieList *movies, UserList *users){
  _totalAverage = 0;
  int count = 0;

  string::size_type size;
  ifstream file(ratingsFileName.c_str());
  string line = "";

	while (getline(file, line)) {
    if(count++ > 0){
      string movieId;
      string userId;
      int rate;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      movieId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      userId = line.substr(0,dotsPosition);
      rate = stoi(line.substr(firstCommaPosition + 1, 1),&size);

      if(_totalAverage == 0){
        _totalAverage = (double)rate;
      } else {
        _totalAverage = ((_totalAverage * (count-1)) + (double)rate)/count;
      }

      if((*movies).find(movieId) != (*movies).end()) { //filme já foi adicionado anteriormente
        ((*movies)[movieId]).views[userId] = rate;
        ((*movies)[movieId]).averageRate = (((*movies)[movieId]).averageRate * ((*movies)[movieId].views.size() - 1) + rate)/((*movies)[movieId]).views.size();
        (*movies)[movieId].sumProductRate += rate * rate;
      } else { //filme não foi adicionado anteriormente
        (*movies)[movieId].views[userId] = rate;
        (*movies)[movieId].averageRate = rate;
        (*movies)[movieId].sumProductRate = rate * rate;
      }

      if((*users).find(userId) != (*users).end()){
        ((*users)[userId])[movieId] = rate;
      } else {
        View vm;
        vm[movieId] = rate;
        (*users)[userId] = vm;
      }
    }
  }

  if(_totalAverage - (int)_totalAverage > 0){
    _totalAverage = (double)((int)_totalAverage + 1);
  }
}