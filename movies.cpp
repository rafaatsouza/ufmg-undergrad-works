#include <iostream>
#include <string>
#include <vector>
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

//retorna a nota media de um filme
int GetMovieAverageRating(MovieList *movies, string movieId){
  View::iterator it;
  int count = 0;
  int sum = 0;


  for(it = (*movies)[movieId].begin(); it != (*movies)[movieId].end(); it++) {
    sum += (*it).second;
    count++;
  }

  return sum/count;
}

double GetSimilarity(MovieList *movies, string movieA, string movieB){
  int countReviewsA = (*movies)[movieA].size();
  int countReviewsB = (*movies)[movieB].size();

  if(countReviewsA == 0 || countReviewsB == 0){
    return -1;
  }

  int countMovies = 0;
  double similarity = 0;
  double minFactor = 1;
  int productSum;
  int sumSquareA;
  int sumSquareB;

  View::iterator it_a;
  View::iterator it_b;

  for(it_a = (*movies)[movieA].begin(); it_a != (*movies)[movieA].end(); it_a++) {
    for(it_b = (*movies)[movieB].begin(); it_b != (*movies)[movieB].end(); it_b++) {
      if((*it_a).first == (*it_b).first){
        productSum += ((*it_a).second * (*it_b).second);
        sumSquareA += ((*it_a).second * (*it_a).second);
        sumSquareB += ((*it_b).second * (*it_b).second);
        countMovies++;
      }
    }
  }

  if(countMovies > 0){
    similarity = productSum / (sqrt(sumSquareA) * sqrt(sumSquareB));

    minFactor = ((double)(GetMin(countMovies,30))/(double)30);
    return similarity * minFactor;
  } else {
    return -1;
  }
}

vector<SimilarityResume> getSimilarityList(string userId, string movieId, MovieList *movies, UserList *users){
  int count = 0;
  vector<SimilarityResume> similarityList((*users)[userId].size());
  View::iterator it;

  for(it = (*users)[userId].begin(); it != (*users)[userId].end(); it++) {
    double similarity = GetSimilarity(movies, movieId, it->first);
    if(similarity > -1){
      similarityList[count].rate = (*it).second;
    }
    similarityList[count].similarity = similarity;
    count++;
  }

  return similarityList;
}

double getPrediction(string userId, string movieId, MovieList *movies, UserList *users){
  if((*users).find(userId) != (*users).end() && (*users)[userId].size() > 0){
    vector<SimilarityResume> similarityList = getSimilarityList(userId, movieId, movies, users);

    double prediction = 0;
    double weight = 0;
    vector<SimilarityResume>::iterator it;

    for(it = similarityList.begin(); it != similarityList.end(); it++) {
      if((*it).similarity > -1){
        prediction = prediction + (((*it).rate) * ((*it).similarity));
        weight += (*it).similarity;
      }
    }

    similarityList.clear();

    if(weight > 0){
      return prediction/weight;
    } else if((*movies).find(movieId) != (*movies).end() && (*movies)[movieId].size() > 0){
      cout << "retornou media" << '\n';
      return GetMovieAverageRating(movies, movieId);
    } else {
      cout << "retornou 6 fixo" << '\n';
      return 6; //TODO: Fix this
    }
  } else if((*movies).find(movieId) != (*movies).end() && (*movies)[movieId].size() > 0){
    cout << "retornou media" << '\n';
    return GetMovieAverageRating(movies, movieId);
  } else {
    cout << "retornou 6 fixo" << '\n';
    return 6; //TODO: Fix this
  }
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
      string movieId;
      string userId;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      movieId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      userId = line.substr(0,dotsPosition);


      cout << line << "," << getPrediction(userId, movieId, movies, users) << '\n';
    } else {
      //cout << "UserId:ItemId,Rating" << '\n';
    }
    count++;
  }
}
