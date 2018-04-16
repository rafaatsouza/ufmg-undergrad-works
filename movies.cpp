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

double GetSimilarity(MovieList *movies, string movieA, string movieB){
  if((*movies)[movieA].similarities.find(movieB) != (*movies)[movieA].similarities.end()){
    return (*movies)[movieA].similarities[movieB];
  } else if((*movies)[movieB].similarities.find(movieA) != (*movies)[movieB].similarities.end()){
    return (*movies)[movieB].similarities[movieA];
  }

  double similarity = 0;
  int countSharedReviews = 0;
  double productSum = 0;

  View::iterator it;

  for(it = (*movies)[movieA].views.begin(); it != (*movies)[movieA].views.end(); it++) {
    if((*movies)[movieB].views.find((*it).first) != (*movies)[movieB].views.end()){
      productSum += ((*it).second * (*movies)[movieB].views[(*it).first]);
      countSharedReviews++;
    }
  }

  if(productSum > 0){
    similarity = (productSum / (sqrt((*movies)[movieA].sumProductRate) * sqrt((*movies)[movieB].sumProductRate)));
  } else {
    similarity = -1;
  }

  (*movies)[movieA].similarities[movieB] = similarity;
  (*movies)[movieB].similarities[movieA] = similarity;
  return similarity;
}

double GetPrediction(string userId, string movieId, MovieList *movies, UserList *users){
  if((*users).find(userId) != (*users).end() && (*users)[userId].size() > 0 && (*movies).find(movieId) != (*movies).end() && (*movies)[movieId].views.size() > 0){
    double prediction = 0;
    double weight = 0;
    View::iterator it;

    for(it = (*users)[userId].begin(); it != (*users)[userId].end(); it++) {
      double similarity = GetSimilarity(movies, movieId, it->first);
      if(similarity > -1){
        double rate = (double)(*it).second - (*movies)[movieId].averageRate;
        if(rate < 0) { rate *= (double)-1; }
        prediction += (similarity * rate);
        weight += similarity;
      }
    }

    if(weight > 0){
      return (*movies)[movieId].averageRate + (prediction/weight);
    } else if((*movies).find(movieId) != (*movies).end() && (*movies)[movieId].views.size() > 0){
      return ((*movies)[movieId]).averageRate;
    } else {
      return _totalAverage;
    }
  } else if((*movies).find(movieId) != (*movies).end() && (*movies)[movieId].views.size() > 0){
    return ((*movies)[movieId]).averageRate;
  } else {
    return _totalAverage;
  }
}

void GetRatings(string filename, MovieList *movies, UserList *users){
  _totalAverage = 0;
  int count = 0;

  string::size_type size;
  ifstream file(filename.c_str());
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

      if((*movies).find(movieId) != (*movies).end()) {
        ((*movies)[movieId]).views[userId] = rate;
        ((*movies)[movieId]).averageRate = (((*movies)[movieId]).averageRate * ((*movies)[movieId].views.size() - 1) + rate)/((*movies)[movieId]).views.size();
        (*movies)[movieId].sumProductRate += rate * rate;
      } else {
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


      cout << line << "," << GetPrediction(userId, movieId, movies, users) << '\n';
    } else if(count == 0) {
      cout << "UserId:ItemId,Prediction" << '\n';
    }
    count++;
  }

  file.close();
}
