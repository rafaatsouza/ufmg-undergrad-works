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

  int countReviewsA = 0;
  int countReviewsB = 0;

  if((*movies).find(movieA) != (*movies).end()){
    countReviewsA = (*movies)[movieA].views.size();
  }
  if((*movies).find(movieB) != (*movies).end()){
   countReviewsB = (*movies)[movieB].views.size(); 
  }

  if(countReviewsA == 0 && countReviewsB == 0){
    (*movies)[movieA].similarities[movieB] = -1;
    (*movies)[movieB].similarities[movieA] = -1;
    return -1;
  }

  double similarity = 0;
  int countSharedReviews = 0;
  int productSum;
  int sumSquareA;
  int sumSquareB;

  View::iterator it_a;
  View::iterator it_b;

  if(countReviewsA > 0){
    for(it_a = (*movies)[movieA].views.begin(); it_a != (*movies)[movieA].views.end(); it_a++) {
      if(countReviewsB > 0 && (*movies)[movieB].views.find((*it_a).first) != (*movies)[movieB].views.end()){
        productSum += ((*it_a).second * (*movies)[movieB].views[(*it_a).first]);
        countSharedReviews++;
      }
      sumSquareA += ((*it_a).second * (*it_a).second);
    }

    if(countReviewsB > 0){
      for(it_b = (*movies)[movieB].views.begin(); it_b != (*movies)[movieB].views.end(); it_b++) {
        sumSquareB += ((*it_b).second * (*it_b).second);
      }
    }
  } else {
    for(it_b = (*movies)[movieB].views.begin(); it_b != (*movies)[movieB].views.end(); it_b++) {
      if(countReviewsA > 0 && (*movies)[movieA].views.find((*it_b).first) != (*movies)[movieA].views.end()){
        productSum += ((*it_b).second * (*movies)[movieA].views[(*it_b).first]);
        countSharedReviews++;
      }
      sumSquareB += ((*it_b).second * (*it_b).second);
    }

    if(countReviewsA > 0){
      for(it_a = (*movies)[movieA].views.begin(); it_a != (*movies)[movieA].views.end(); it_a++) {
        sumSquareA += ((*it_a).second * (*it_a).second);
      }
    }
  }

  if(productSum > 0){
    similarity = (productSum / (sqrt(sumSquareA) * sqrt(sumSquareB)));
  } else {
    similarity = -1;
  }

    (*movies)[movieA].similarities[movieB] = similarity;
    (*movies)[movieB].similarities[movieA] = similarity;
    return similarity;
}

double getPrediction(string userId, string movieId, MovieList *movies, UserList *users){
  if((*users).find(userId) != (*users).end() && (*users)[userId].views.size() > 0){
    double prediction = 0;
    double weight = 0;
    View::iterator it;

    for(it = (*users)[userId].views.begin(); it != (*users)[userId].views.end(); it++) {
      double similarity = GetSimilarity(movies, movieId, it->first);
      if(similarity > -1){
        int rate = ((*it).second - (*users)[userId].averageRate);
        if(rate < 0) { rate *= -1; }
        prediction = prediction + (similarity * rate);
        weight += similarity;
      }
    }

    if(weight > 0){
      return prediction/weight;
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
      } else {
        (*movies)[movieId].views[userId] = rate;
        (*movies)[movieId].averageRate = rate;
      }

      if((*users).find(userId) != (*users).end()){
        ((*users)[userId]).views[movieId] = rate;
        ((*users)[userId]).averageRate = (((*users)[userId]).averageRate * ((*users)[userId].views.size() - 1) + rate)/((*users)[userId]).views.size();
      } else {
        (*users)[userId].views[movieId] = rate;
        (*users)[userId].averageRate = rate;
      }
    }
  }

  file.close();
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


      cout << line << "," << getPrediction(userId, movieId, movies, users) << '\n';
    } else if(count == 0) {
      cout << "UserId:ItemId,Prediction" << '\n';
    }
    count++;
  }

  file.close();
}