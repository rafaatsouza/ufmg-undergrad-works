#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <math.h>
#include "movies.hpp"
#include "movieJson.hpp"

using namespace std;

#define SIM_BASE_COUNTRY 1.0
#define SIM_BASE_PERSON 1.0
#define SIM_BASE_LANGUAGE 1.0
#define SIM_BASE_GENRE 30.0
#define YEAR_BOOST 1.2;
#define AWARDS_BOOST 1.2;
#define MIN_IMDB_VOTES 300

double _totalAverage;

void SetsUserSimilarityMap(MovieList *movies, UserList *users, string userId){
  if(((*users)[userId]).simGenre.size() == 0 || ((*users)[userId]).simCountry.size() == 0 || ((*users)[userId]).simPerson.size() == 0 || (*users)[userId].averageYear < 0){
    vector<int> years;
    viewIterator it;
    simIterator its;
    
    for(it = (*users)[userId].views.begin(); it != (*users)[userId].views.end(); it++){
      if((*movies)[it->first].content.Year > 0){
        years.push_back((*movies)[it->first].content.Year);
        if(years.size() == 1){
          (*users)[userId].averageYear = (*movies)[it->first].content.Year;
        } else {
          (*users)[userId].averageYear = ((years.size() - 1) * (*users)[userId].averageYear + (*movies)[it->first].content.Year)/years.size();
        }
      }

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

      for(its = (*movies)[it->first].simLanguage.begin(); its != (*movies)[it->first].simLanguage.end(); its++){
        if(((*users)[userId]).simLanguage.find(its->first) != ((*users)[userId]).simLanguage.end()){
          ((*users)[userId]).simLanguage[its->first] += its->second;
        } else {
          ((*users)[userId]).simLanguage[its->first] = its->second;
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

    if(years.size() > 0){
      double sum = 0;
      vector<int>::iterator it;
      for(it = years.begin(); it != years.end(); it++){
        sum = ((*it) - (*users)[userId].averageYear) * ((*it) - (*users)[userId].averageYear);
      }
      (*users)[userId].yearDeviation = sum/years.size();
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

  for(it = (*movies)[movieId].simLanguage.begin(); it != (*movies)[movieId].simLanguage.end(); it++){
    if((*users)[userId].simLanguage.find(it->first) != (*users)[userId].simLanguage.end()){
      sum += it->second * (*users)[userId].simLanguage[it->first];
      sqrtu += (*users)[userId].simLanguage[it->first] * (*users)[userId].simLanguage[it->first];
    }
    sqrti += it->second * it->second;
  }

  for(it = (*users)[userId].simLanguage.begin(); it != (*users)[userId].simLanguage.end(); it++){
    if((*movies)[movieId].simLanguage.find(it->first) == (*movies)[movieId].simLanguage.end()){
      sqrtu += it->second * it->second; 
    }
  }

  result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_LANGUAGE;

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

  result = ((double)10) * (result/(SIM_BASE_COUNTRY + SIM_BASE_GENRE + SIM_BASE_PERSON + SIM_BASE_LANGUAGE));

  if((*movies)[movieId].content.Year > 0 && (*users)[userId].averageYear > 0){
    double bottom = (*users)[userId].averageYear - (*users)[userId].yearDeviation;
    double top = (*users)[userId].averageYear + (*users)[userId].yearDeviation;

    if(bottom <= (*movies)[movieId].content.Year && top >= (*movies)[movieId].content.Year){
      result *= YEAR_BOOST;
    }
  }

  if((*movies)[movieId].content.hasAwardsWin == true){
    result *= AWARDS_BOOST;
  }

  if(((*movies)[movieId]).content.imdbRating > 0){
    return ((*movies)[movieId].content.imdbRating + result)/2;
  } else {
    return result;
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
    int firstCommaPosition = line.find(",");
    
    string movieId = line.substr(0, firstCommaPosition);
    string jsonText = line.substr(firstCommaPosition + 1);
    
    if((*movies).find(movieId) != (*movies).end()) {
      if(GetMovieResponse(jsonText) == true){
        vector<string>::iterator it;

        ((*movies)[movieId]).content.Response = true;

        ((*movies)[movieId]).content.Year = GetMovieYear(jsonText);
        ((*movies)[movieId]).content.imdbRating = GetMovieImdbRating(jsonText, MIN_IMDB_VOTES);
        ((*movies)[movieId]).content.hasAwardsWin = GetMovieAwards(jsonText);

        ((*movies)[movieId]).content.Genre = GetMovieGenreVector(jsonText);
        ((*movies)[movieId]).content.Country = GetMovieCountryVector(jsonText);
        ((*movies)[movieId]).content.Language = GetMovieLanguageVector(jsonText);
        ((*movies)[movieId]).content.Persons = GetMoviePersonVector(jsonText);

        for(it = ((*movies)[movieId]).content.Genre.begin(); it != ((*movies)[movieId]).content.Genre.end(); it++){
          ((*movies)[movieId]).simGenre[(*it)] = 1.0;
        }

        for(it = ((*movies)[movieId]).content.Country.begin(); it != ((*movies)[movieId]).content.Country.end(); it++){
          ((*movies)[movieId]).simCountry[(*it)] = 1.0;
        }

        for(it = ((*movies)[movieId]).content.Language.begin(); it != ((*movies)[movieId]).content.Language.end(); it++){
          ((*movies)[movieId]).simLanguage[(*it)] = 1.0;
        }

        for(it = ((*movies)[movieId]).content.Persons.begin(); it != ((*movies)[movieId]).content.Persons.end(); it++){
          ((*movies)[movieId]).simPerson[(*it)] = 1.0;
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
      ((*users)[userId]).averageYear = -1;
    }
  }

  if(_totalAverage - (int)_totalAverage > 0){
    _totalAverage = (double)((int)_totalAverage + 1);
  }

  GetMoviesContent(movies, contentFileName);
}