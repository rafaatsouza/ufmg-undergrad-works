#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "movies.hpp"
#include "rapidjson/document.h"
#include "stringMethods.hpp"

using namespace std;
using namespace rapidjson;

double _totalAverage;

double GetPrediction(){
  return _totalAverage;
}

void printMovieString(MovieList *movies, string movieId){ //tests only
  if((*movies).find(movieId) != (*movies).end() && ((*movies)[movieId]).content.Response == true) {
    cout << "Filme: " << movieId << " "; 
     vector<string>::iterator it;
     cout << "Ano: " << ((*movies)[movieId]).content.Year;  
     
     if(((*movies)[movieId]).content.Genre.size() > 0){
       cout << "- Generos: ";  
       for(it = (*movies)[movieId].content.Genre.begin(); it != (*movies)[movieId].content.Genre.end(); it++) {
         cout << *it << ";";
       }
     } else {
       cout << "- sem generos ";  
     }

     if(((*movies)[movieId]).content.Country.size() > 0){
       cout << "- Paises: ";  
       for(it = (*movies)[movieId].content.Country.begin(); it != (*movies)[movieId].content.Country.end(); it++) {
         cout << *it << ";";
       }
     } else {
       cout << "- sem Paises ";  
     } 

     if(((*movies)[movieId]).content.Persons.size() > 0){
       cout << "- Pessoas: ";  
       for(it = (*movies)[movieId].content.Persons.begin(); it != (*movies)[movieId].content.Persons.end(); it++) {
         cout << *it << ";";
       }
     } else {
       cout << "- sem Pessoas ";  
     }

     cout << '\n';
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


      cout << line << "," << GetPrediction() << '\n';
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
    
    if((*movies).find(movieId) != (*movies).end()) { //filme já foi adicionado anteriormente
        Document document;
        document.Parse(jsonText.c_str());
        
        if(!((string)document["Response"].GetString()).compare("True")){
          ((*movies)[movieId]).content.Response = true;
          if(!((string)document["Year"].GetString()).compare("N/A")){
            ((*movies)[movieId]).content.Year = -1;  
          } else {
            ((*movies)[movieId]).content.Year = stoi(document["Year"].GetString());
          }

          if(((string)document["Genre"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Genre"].GetString(), false))){
              ((*movies)[movieId]).content.Genre.push_back(s);
            }
          }

          if(((string)document["Country"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Country"].GetString(), false))){
              ((*movies)[movieId]).content.Country.push_back(s);
            }
          }

          if(((string)document["Director"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Director"].GetString(), true))){
              ((*movies)[movieId]).content.Persons.push_back(s);
            }
          }

          if(((string)document["Writer"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Writer"].GetString(), true))){
              ((*movies)[movieId]).content.Persons.push_back(s);
            }
          }

          if(((string)document["Actors"].GetString()).compare("N/A")){
            for(string& s: (SplitStringByComma(document["Actors"].GetString(), true))){
              ((*movies)[movieId]).content.Persons.push_back(s);
            }
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

  GetMoviesContent(movies, contentFileName);
}