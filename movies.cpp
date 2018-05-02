#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <math.h>
#include "movies.hpp"
#include "rapidjson/document.h"
#include "stringMethods.hpp"

using namespace std;
using namespace rapidjson;

#define SIM_BASE_COUNTRY 1.0
#define SIM_BASE_PERSON 1.0
#define SIM_BASE_GENRE 30.0
#define MIN_IMDB_VOTES 300

double _totalAverage;

void SetsUserSimilarityMap(MovieList *movies, UserList *users, string userId){
  if(((*users)[userId]).simGenre.size() == 0 || ((*users)[userId]).simCountry.size() == 0 || ((*users)[userId]).simPerson.size() == 0){
    viewIterator it;
    simIterator its;
    
    for(it = (*users)[userId].views.begin(); it != (*users)[userId].views.end(); it++){
      for(its = (*movies)[it->first].simGenre.begin(); its != (*movies)[it->first].simGenre.end(); its++){
        if(((*users)[userId]).simGenre.find(its->first) != ((*users)[userId]).simGenre.end()){
          ((*users)[userId]).simGenre[its->first] += its->second;
        } else {
          ((*users)[userId]).simGenre[its->first] = its->second;
        }
      }

      for(its = (*movies)[it->first].simCountry.begin(); its != (*movies)[it->first].simCountry.end(); its++){
        if(((*users)[userId]).simCountry.find(its->first) != ((*users)[userId]).simCountry.end()){
          ((*users)[userId]).simCountry[its->first] += its->second;
        } else {
          ((*users)[userId]).simCountry[its->first] = its->second;
        }
      }

      for(its = (*movies)[it->first].simPerson.begin(); its != (*movies)[it->first].simPerson.end(); its++){
        if(((*users)[userId]).simPerson.find(its->first) != ((*users)[userId]).simPerson.end()){
          ((*users)[userId]).simPerson[its->first] += its->second;
        } else {
          ((*users)[userId]).simPerson[its->first] = its->second;
        }
      }
    }
  }
}

double GetContentBaseRating(MovieList *movies, UserList *users, string movieId, string userId){  
  double result = 0;
  double sum = 0.0, sqrtu = 0.0, sqrti = 0.0;
  simIterator it;

  SetsUserSimilarityMap(movies, users, userId);

  if((*movies)[movieId].content.Country.size() > 0){
    for(it = (*movies)[movieId].simCountry.begin(); it != (*movies)[movieId].simCountry.end(); it++){
      if((*users)[userId].simCountry.find(it->first) != (*users)[userId].simCountry.end()){
        sum += it->second * (*users)[userId].simCountry[it->first];
        sqrtu += (*users)[userId].simCountry[it->first] * (*users)[userId].simCountry[it->first];
      }
      sqrti += it->second * it->second;
    }

    for(it = (*users)[userId].simCountry.begin(); it != (*users)[userId].simCountry.end(); it++){
      if((*movies)[movieId].simCountry.find(it->first) == (*movies)[movieId].simCountry.end()){
        sqrtu += it->second * it->second; 
      }
    }

    result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_COUNTRY; 
  }

  for(it = (*movies)[movieId].simGenre.begin(); it != (*movies)[movieId].simGenre.end(); it++){
    if((*users)[userId].simGenre.find(it->first) != (*users)[userId].simGenre.end()){
      sum += it->second * (*users)[userId].simGenre[it->first];
      sqrtu += (*users)[userId].simGenre[it->first] * (*users)[userId].simGenre[it->first];
    }
    sqrti += it->second * it->second;
  }

  for(it = (*users)[userId].simGenre.begin(); it != (*users)[userId].simGenre.end(); it++){
    if((*movies)[movieId].simGenre.find(it->first) == (*movies)[movieId].simGenre.end()){
      sqrtu += it->second * it->second; 
    }
  }

  result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_GENRE;

  for(it = (*movies)[movieId].simPerson.begin(); it != (*movies)[movieId].simPerson.end(); it++){
    if((*users)[userId].simPerson.find(it->first) != (*users)[userId].simPerson.end()){
      sum += it->second * (*users)[userId].simPerson[it->first];
      sqrtu += (*users)[userId].simPerson[it->first] * (*users)[userId].simPerson[it->first];
    }
    sqrti += it->second * it->second;
  }

  for(it = (*users)[userId].simPerson.begin(); it != (*users)[userId].simPerson.end(); it++){
    if((*movies)[movieId].simPerson.find(it->first) == (*movies)[movieId].simPerson.end()){
      sqrtu += it->second * it->second; 
    }
  }

  result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_PERSON;

  if(((*movies)[movieId]).content.imdbRating > 0){
    return (((*movies)[movieId]).content.imdbRating + ((double)10) * (result/(SIM_BASE_COUNTRY + SIM_BASE_GENRE + SIM_BASE_PERSON)))/2;
  } else {
    return ((double)10) * (result/(SIM_BASE_COUNTRY + SIM_BASE_GENRE + SIM_BASE_PERSON));
  }
}

double GetPrediction(MovieList *movies, UserList *users, string movieId, string userId){
  if((*users).find(userId) != (*users).end() && (*users)[userId].views.size() > 0
    && (*movies).find(movieId) != (*movies).end() && ((*movies)[movieId]).content.Response == true){
    return GetContentBaseRating(movies, users, movieId, userId);
  } else if((*movies).find(movieId) != (*movies).end() && ((*movies)[movieId]).content.Response == true 
            && ((*movies)[movieId]).content.imdbRating > 0){
    return ((*movies)[movieId]).content.imdbRating;
  } else {
    return _totalAverage;
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

      cout << line << "," << GetPrediction(movies, users, movieId, userId) << '\n';
      //printMovieString(movies, movieId);
    } else if(count == 0) {
      cout << "UserId:ItemId,Prediction" << '\n';
    }
    count++;
  }

  file.close();
}

void GetMoviesContent(MovieList *movies, string contentFileName){
  ifstream file(contentFileName.c_str());
  string line = "";

	while (getline(file, line)) {
    Value::ConstMemberIterator itr;
    int firstCommaPosition = line.find(",");
    
    string movieId = line.substr(0, firstCommaPosition);
    string jsonText = line.substr(firstCommaPosition + 1);
    
    if((*movies).find(movieId) != (*movies).end()) {
        Document document;
        document.Parse(jsonText.c_str());
        
        if(!((string)document["Response"].GetString()).compare("True")){
          int imdbVotes = -1;

          ((*movies)[movieId]).content.Response = true;

          if(((string)document["Genre"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Genre"].GetString(), false))){
              ((*movies)[movieId]).content.Genre.push_back(s);
              ((*movies)[movieId]).simGenre[s] = 1.0;
            }
          }

          if(((string)document["Country"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Country"].GetString(), false))){
              ((*movies)[movieId]).content.Country.push_back(s);
              ((*movies)[movieId]).simCountry[s] = 1.0;
            }
          }

          if(((string)document["Director"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Director"].GetString(), true))){
              ((*movies)[movieId]).content.Persons.push_back(s);
              ((*movies)[movieId]).simPerson[s] = 1.0;
            }
          }

          if(((string)document["Writer"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Writer"].GetString(), true))){
              ((*movies)[movieId]).content.Persons.push_back(s);
              ((*movies)[movieId]).simPerson[s] = 1.0;
            }
          }

          if(((string)document["Actors"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Actors"].GetString(), true))){
              ((*movies)[movieId]).content.Persons.push_back(s);
              ((*movies)[movieId]).simPerson[s] = 1.0;
            }
          }

          if(((string)document["imdbRating"].GetString()).compare("N/A") && ((string)document["imdbVotes"].GetString()).compare("N/A")){
            imdbVotes = stoi(RemoveComma(document["imdbVotes"].GetString()));
          }

          if(imdbVotes >= MIN_IMDB_VOTES){
             ((*movies)[movieId]).content.imdbRating = stod(document["imdbRating"].GetString());
          } else {
            ((*movies)[movieId]).content.imdbRating = -1.0;
          }
        } else {
          ((*movies)[movieId]).content.Response = false;
        }
      }
  }
}

void GetMoviesInfo(string ratingsFileName, string contentFileName, MovieList *movies, UserList *users){
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

      if((*movies).find(movieId) != (*movies).end()) {
        ((*movies)[movieId]).views[userId] = rate;
        ((*movies)[movieId]).averageRate = (((*movies)[movieId]).averageRate * ((*movies)[movieId].views.size() - 1) + rate)/((*movies)[movieId]).views.size();
        (*movies)[movieId].sumProductRate += rate * rate;
      } else {
        (*movies)[movieId].views[userId] = rate;
        (*movies)[movieId].averageRate = rate;
        (*movies)[movieId].sumProductRate = rate * rate;
        (*movies)[movieId].content.Response = false;
      }

      ((*users)[userId]).views[movieId] = rate;
    }
  }

  if(_totalAverage - (int)_totalAverage > 0){
    _totalAverage = (double)((int)_totalAverage + 1);
  }

  GetMoviesContent(movies, contentFileName);
}