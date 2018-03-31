#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <math.h>
#include "movies.h"

using namespace std;

//retorna o menor número
int GetMin(int a, int b){
  if(a < b){
    return a;
  }
  return b;
}

double GetSimilarity(MovieList *movies, string movieA, string movieB){
  if((*movies)[movieA].similarities.find(movieB) != (*movies)[movieA].similarities.end()){
    return (*movies)[movieA].similarities[movieB];
  } else if((*movies)[movieB].similarities.find(movieA) != (*movies)[movieB].similarities.end()){
    return (*movies)[movieB].similarities[movieA];
  }

  int countReviewsA = (*movies)[movieA].views.size();
  int countReviewsB = (*movies)[movieB].views.size();

  if(countReviewsA == 0 || countReviewsB == 0){
    (*movies)[movieA].similarities[movieB] = -1;
    (*movies)[movieB].similarities[movieA] = -1;
    return -1;
  }

  int countMovies = 0;
  double similarity = 0;
  int productSum;
  int sumSquareA;
  int sumSquareB;

  View::iterator it_a;
  View::iterator it_b;

  for(it_a = (*movies)[movieA].views.begin(); it_a != (*movies)[movieA].views.end(); it_a++) {
    for(it_b = (*movies)[movieB].views.begin(); it_b != (*movies)[movieB].views.end(); it_b++) {
      if((*it_a).first == (*it_b).first){
        productSum += ((*it_a).second * (*it_b).second);
        sumSquareA += ((*it_a).second * (*it_a).second);
        sumSquareB += ((*it_b).second * (*it_b).second);
        countMovies++;
      }
    }
  }

  if(countMovies > 0){
    similarity = (productSum / (sqrt(sumSquareA) * sqrt(sumSquareB))) * ((double)(GetMin(countMovies,30))/(double)30);

    (*movies)[movieA].similarities[movieB] = similarity;
    (*movies)[movieB].similarities[movieA] = similarity;
    return similarity;

  } else {
    (*movies)[movieA].similarities[movieB] = -1;
    (*movies)[movieB].similarities[movieA] = -1;
    return -1;
  }
}

double getPrediction(string userId, string movieId, MovieList *movies, UserList *users){
  if((*users).find(userId) != (*users).end() && (*users)[userId].size() > 0){
    double prediction = 0;
    double weight = 0;
    View::iterator it;

    for(it = (*users)[userId].begin(); it != (*users)[userId].end(); it++) {
      double similarity = GetSimilarity(movies, movieId, it->first);
      if(similarity > -1){
        prediction = prediction + ((*it).second * similarity);
        weight += similarity;
      }
    }

    if(weight > 0){
      return prediction/weight;
    } else if((*movies).find(movieId) != (*movies).end() && (*movies)[movieId].views.size() > 0){
      return ((*movies)[movieId]).averageRate;
    } else {
      return (double)6; //TODO: Fix this
    }
  } else if((*movies).find(movieId) != (*movies).end() && (*movies)[movieId].views.size() > 0){
    return ((*movies)[movieId]).averageRate;
  } else {
    return (double)6; //TODO: Fix this
  }
}

void GetRatings(string filename, MovieList *movies, UserList *users){
  int count = 0;
  string::size_type size;
  ifstream file(filename.c_str());
  string line = "";

	while (getline(file, line)) {
    if(count > 0){
      string movieId;
      string userId;
      int rate;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      movieId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      userId = line.substr(0,dotsPosition);
      rate = stoi(line.substr(firstCommaPosition + 1, 1),&size);

      if((*movies).find(movieId) != (*movies).end()) {
        ((*movies)[movieId]).views[userId] = rate;
        ((*movies)[movieId]).averageRate = (((*movies)[movieId]).averageRate * ((*movies)[movieId]).views.size() - 1 + rate)/((*movies)[movieId]).views.size();
      } else {
        (*movies)[movieId].views[userId] = rate;
        (*movies)[movieId].averageRate = rate;
      }

      if((*users).find(userId) != (*users).end()){
        ((*users)[userId])[movieId] = rate;
      } else {
        View vm;
        vm[movieId] = rate;

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
      string movieId;
      string userId;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      movieId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      userId = line.substr(0,dotsPosition);


      cout << line << "," << getPrediction(userId, movieId, movies, users) << '\n';
    } else {
      cout << "UserId:ItemId,Rating" << '\n';
    }
    count++;
  }
}
