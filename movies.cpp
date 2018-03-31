#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "movies.h"

using namespace std;

int GetMovieAverageRating(MovieList *movies, string movieId){
  if((*movies).find(movieId) != (*movies).end() && (*movies)[movieId].size() > 0){
    View::iterator it;
    int count = 0;
    int sum = 0;


    for(it = (*movies)[movieId].begin(); it != (*movies)[movieId].end(); it++) {
      sum += (*it).second;
      count++;
    }

    return sum/count;
  } else {
    return 6; //TODO: Fix this
  }
}

int GetSimilarity(MovieList *movies, string movieA, string movieB){
  return 1;
}

vector<SimilarityResume> getSimilarityList(string userId, string movieId, MovieList *movies, UserList *users){
  int count = 0;
  vector<SimilarityResume> similarityList((*users)[userId].size());
  View::iterator it;

  for(it = (*users)[userId].begin(); it != (*users)[userId].end(); it++) {
    similarityList[count].rate = (*it).second;
    similarityList[count].similarity = GetSimilarity(movies, movieId, it->first);
  }

  return similarityList;
}

int getPrediction(string userId, string movieId, MovieList *movies, UserList *users){
  if((*users).find(userId) != (*users).end() && (*users)[userId].size() > 0){
    vector<SimilarityResume> similarityList = getSimilarityList(userId, movieId, movies, users);

    int prediction = 0;
    double weight = 0;
    vector<SimilarityResume>::iterator it;

    for(it = similarityList.begin(); it != similarityList.end(); it++) {
      prediction += (((*it).rate) * ((*it).similarity));
      weight += (*it).similarity;
    }

    similarityList.clear();

    return prediction/weight;
  } else {
    return GetMovieAverageRating(movies, movieId);
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
