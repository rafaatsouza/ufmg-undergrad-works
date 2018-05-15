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
#define SIM_BASE_PLOT 128.0
#define SIM_BASE_GENRE 30.0
#define YEAR_BOOST 1.2;
#define AWARDS_BOOST 1.2;
#define MIN_IMDB_VOTES 300

double _totalAverage;

void SetsUserSimilarityMap(MovieList *movies, UserList *users, string userId){
  if(((*users)[userId]).Genre.size() == 0 || ((*users)[userId]).Country.size() == 0
      || ((*users)[userId]).Person.size() == 0 || (*users)[userId].averageYear < 0
      || ((*users)[userId]).Plot.size() == 0){
    vector<int> years;
    viewIterator it;
    TermQuantityIterator its;

    for(it = (*users)[userId].views.begin(); it != (*users)[userId].views.end(); it++){
      if((*movies)[it->first].Year > 0){
        years.push_back((*movies)[it->first].Year);
        if(years.size() == 1){
          (*users)[userId].averageYear = (*movies)[it->first].Year;
        } else {
          (*users)[userId].averageYear = ((years.size() - 1) * (*users)[userId].averageYear + (*movies)[it->first].Year)/years.size();
        }
      }

      for(its = (*movies)[it->first].Genre.begin(); its != (*movies)[it->first].Genre.end(); its++){
        if(((*users)[userId]).Genre.find(its->first) != ((*users)[userId]).Genre.end()){
          ((*users)[userId]).Genre[its->first] += its->second;
        } else {
          ((*users)[userId]).Genre[its->first] = its->second;
        }
      }

      for(its = (*movies)[it->first].Country.begin(); its != (*movies)[it->first].Country.end(); its++){
        if(((*users)[userId]).Country.find(its->first) != ((*users)[userId]).Country.end()){
          ((*users)[userId]).Country[its->first] += its->second;
        } else {
          ((*users)[userId]).Country[its->first] = its->second;
        }
      }

      for(its = (*movies)[it->first].Language.begin(); its != (*movies)[it->first].Language.end(); its++){
        if(((*users)[userId]).Language.find(its->first) != ((*users)[userId]).Language.end()){
          ((*users)[userId]).Language[its->first] += its->second;
        } else {
          ((*users)[userId]).Language[its->first] = its->second;
        }
      }

      for(its = (*movies)[it->first].Person.begin(); its != (*movies)[it->first].Person.end(); its++){
        if(((*users)[userId]).Person.find(its->first) != ((*users)[userId]).Person.end()){
          ((*users)[userId]).Person[its->first] += its->second;
        } else {
          ((*users)[userId]).Person[its->first] = its->second;
        }
      }

      for(its = (*movies)[it->first].Plot.begin(); its != (*movies)[it->first].Plot.end(); its++){
        if(((*users)[userId]).Plot.find(its->first) != ((*users)[userId]).Plot.end()){
          ((*users)[userId]).Plot[its->first] += its->second;
        } else {
          ((*users)[userId]).Plot[its->first] = its->second;
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
  double sum = 0.0, sumd = 0.0, sqrtu = 0.0, sqrti = 0.0;
  TermQuantityIterator it;

  SetsUserSimilarityMap(movies, users, userId);

  if((*movies)[movieId].Country.size() > 0){
    for(it = (*movies)[movieId].Country.begin(); it != (*movies)[movieId].Country.end(); it++){
      if((*users)[userId].Country.find(it->first) != (*users)[userId].Country.end()){
        sum += it->second * (*users)[userId].Country[it->first];
        sqrtu += (*users)[userId].Country[it->first] * (*users)[userId].Country[it->first];
      }
      sqrti += it->second * it->second;
    }

    for(it = (*users)[userId].Country.begin(); it != (*users)[userId].Country.end(); it++){
      if((*movies)[movieId].Country.find(it->first) == (*movies)[movieId].Country.end()){
        sqrtu += it->second * it->second;
      }
    }

    result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_COUNTRY;
    sumd += SIM_BASE_COUNTRY;
    sum = 0.0;
    sqrtu = 0.0;
    sqrti = 0.0;
  }

  if((*movies)[movieId].Genre.size() > 0){
    for(it = (*movies)[movieId].Genre.begin(); it != (*movies)[movieId].Genre.end(); it++){
      if((*users)[userId].Genre.find(it->first) != (*users)[userId].Genre.end()){
        sum += it->second * (*users)[userId].Genre[it->first];
        sqrtu += (*users)[userId].Genre[it->first] * (*users)[userId].Genre[it->first];
      }
      sqrti += it->second * it->second;
    }

    for(it = (*users)[userId].Genre.begin(); it != (*users)[userId].Genre.end(); it++){
      if((*movies)[movieId].Genre.find(it->first) == (*movies)[movieId].Genre.end()){
        sqrtu += it->second * it->second;
      }
    }

    sumd += SIM_BASE_GENRE;
    result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_GENRE;
    sum = 0.0;
    sqrtu = 0.0;
    sqrti = 0.0;
  }

  if((*movies)[movieId].Language.size() > 0){
    for(it = (*movies)[movieId].Language.begin(); it != (*movies)[movieId].Language.end(); it++){
      if((*users)[userId].Language.find(it->first) != (*users)[userId].Language.end()){
        sum += it->second * (*users)[userId].Language[it->first];
        sqrtu += (*users)[userId].Language[it->first] * (*users)[userId].Language[it->first];
      }
      sqrti += it->second * it->second;
    }

    for(it = (*users)[userId].Language.begin(); it != (*users)[userId].Language.end(); it++){
      if((*movies)[movieId].Language.find(it->first) == (*movies)[movieId].Language.end()){
        sqrtu += it->second * it->second;
      }
    }

    sumd += SIM_BASE_LANGUAGE;
    result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_LANGUAGE;
    sum = 0.0;
    sqrtu = 0.0;
    sqrti = 0.0;
  }

  if((*movies)[movieId].Person.size() > 0){
    for(it = (*movies)[movieId].Person.begin(); it != (*movies)[movieId].Person.end(); it++){
      if((*users)[userId].Person.find(it->first) != (*users)[userId].Person.end()){
        sum += it->second * (*users)[userId].Person[it->first];
        sqrtu += (*users)[userId].Person[it->first] * (*users)[userId].Person[it->first];
      }
      sqrti += it->second * it->second;
    }

    for(it = (*users)[userId].Person.begin(); it != (*users)[userId].Person.end(); it++){
      if((*movies)[movieId].Person.find(it->first) == (*movies)[movieId].Person.end()){
        sqrtu += it->second * it->second;
      }
    }

    sumd += SIM_BASE_PERSON;
    result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_PERSON;
    sum = 0.0;
    sqrtu = 0.0;
    sqrti = 0.0;
  }

  if((*movies)[movieId].Plot.size() > 0){
    for(it = (*movies)[movieId].Plot.begin(); it != (*movies)[movieId].Plot.end(); it++){
      if((*users)[userId].Plot.find(it->first) != (*users)[userId].Plot.end()){
        sum += it->second * (*users)[userId].Plot[it->first];
        sqrtu += (*users)[userId].Plot[it->first] * (*users)[userId].Plot[it->first];
      }
      sqrti += it->second * it->second;
    }

    for(it = (*users)[userId].Plot.begin(); it != (*users)[userId].Plot.end(); it++){
      if((*movies)[movieId].Plot.find(it->first) == (*movies)[movieId].Plot.end()){
        sqrtu += it->second * it->second;
      }
    }

    sumd += SIM_BASE_PLOT;
    result += (sum/(sqrt(sqrti) * sqrt(sqrtu))) * SIM_BASE_PLOT;
    sum = 0.0;
    sqrtu = 0.0;
    sqrti = 0.0;
  }

  result = ((double)10) * (result/sumd);

  if((*movies)[movieId].Year > 0 && (*users)[userId].averageYear > 0){
    double bottom = (*users)[userId].averageYear - (*users)[userId].yearDeviation;
    double top = (*users)[userId].averageYear + (*users)[userId].yearDeviation;

    if(bottom <= (*movies)[movieId].Year && top >= (*movies)[movieId].Year){
      result *= YEAR_BOOST;
    }
  }

  if((*movies)[movieId].hasAwardsWin == true){
    result *= AWARDS_BOOST;
  }

  if(((*movies)[movieId]).imdbRating > 0){
    return ((*movies)[movieId].imdbRating + result)/2;
  } else {
    return result;
  }
}

double GetPrediction(MovieList *movies, UserList *users, string movieId, string userId){
  if((*users).find(userId) != (*users).end() && (*users)[userId].views.size() > 0
    && (*movies).find(movieId) != (*movies).end() && ((*movies)[movieId]).Response == true){
    return GetContentBaseRating(movies, users, movieId, userId);
  } else {
    return _totalAverage;
  }
}

void PrintPredictions(string filename, MovieList *movies, UserList *users){
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
        vector<string> tempVector;
        vector<string>::iterator it;

        ((*movies)[movieId]).Response = true;

        ((*movies)[movieId]).Year = GetMovieYear(jsonText);
        ((*movies)[movieId]).imdbRating = GetMovieImdbRating(jsonText, MIN_IMDB_VOTES);
        ((*movies)[movieId]).hasAwardsWin = GetMovieAwards(jsonText);
        ((*movies)[movieId]).Plot = GetMoviePlotTermVector(jsonText);

        tempVector = GetMovieGenreVector(jsonText);
        for(it = tempVector.begin(); it != tempVector.end(); it++){
          ((*movies)[movieId]).Genre[(*it)] = 1.0;
        }

        tempVector = GetMovieCountryVector(jsonText);
        for(it = tempVector.begin(); it != tempVector.end(); it++){
          ((*movies)[movieId]).Country[(*it)] = 1.0;
        }

        tempVector = GetMovieLanguageVector(jsonText);
        for(it = tempVector.begin(); it != tempVector.end(); it++){
          ((*movies)[movieId]).Language[(*it)] = 1.0;
        }

        tempVector = GetMoviePersonVector(jsonText);;
        for(it = tempVector.begin(); it != tempVector.end(); it++){
          ((*movies)[movieId]).Person[(*it)] = 1.0;
        }

      } else {
        ((*movies)[movieId]).Response = false;
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

      if((*movies).find(movieId) == (*movies).end()) {
        (*movies)[movieId].Response = false;
      }

      (*movies)[movieId].views[userId] = rate;

      ((*users)[userId]).views[movieId] = rate;
      ((*users)[userId]).averageYear = -1;
    }
  }

  if(_totalAverage - (int)_totalAverage > 0){
    _totalAverage = (double)((int)_totalAverage + 1);
  }

  GetMoviesContent(movies, contentFileName);
}
