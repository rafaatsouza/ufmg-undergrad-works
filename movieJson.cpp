#include <string>
#include <map>
#include <vector>
#include "movieJson.hpp"
#include "rapidjson/document.h"
#include "stringMethods.hpp"

using namespace std;
using namespace rapidjson;

vector<string> GetMovieGenreVector(string json){
    Document document;
    document.Parse(json.c_str());
    vector<string> result;

    if(((string)document["Genre"].GetString()).compare("N/A")){
        for(string& s: (SplitString(document["Genre"].GetString(), false, ','))){
            result.push_back(s);
        }
    }

    return result;
}

vector<string> GetMovieCountryVector(string json){
    Document document;
    document.Parse(json.c_str());
    vector<string> result;

    if(((string)document["Country"].GetString()).compare("N/A")){
        for(string& s: (SplitString(document["Country"].GetString(), false, ','))){
            result.push_back(s);
        }
    }

    return result;
}

vector<string> GetMovieLanguageVector(string json){
    Document document;
    document.Parse(json.c_str());
    vector<string> result;

    if(((string)document["Language"].GetString()).compare("N/A")){
        for(string& s: (SplitString(document["Language"].GetString(), false, ','))){
            result.push_back(s);
        }
    }

    return result;
}

map<string,int> GetMoviePlotTermVector(string json){
    Document document;
    document.Parse(json.c_str());
    map<string,int> result;

    if(((string)document["Plot"].GetString()).compare("N/A")){
        string plot;
        for(char& c : ((string)document["Plot"].GetString())) {
            if(c != ',' && c != '.' && c != '(' && c != ')'){
              plot += c;
            }
        }
        for(string& s: (SplitString(plot, false, ' '))){
            if(result.find(s) != result.end()){
              result[s] += 1;
            } else {
              result[s] = 1;
            }
        }
    }

    return result;
}

vector<string> GetMoviePersonVector(string json){
    Document document;
    document.Parse(json.c_str());
    vector<string> result;

    if(((string)document["Director"].GetString()).compare("N/A")){
        for(string& s: (SplitString(document["Director"].GetString(), true, ','))){
            result.push_back(s);
        }
    }

    if(((string)document["Writer"].GetString()).compare("N/A")){
        for(string& s: (SplitString(document["Writer"].GetString(), true, ','))){
            result.push_back(s);
        }
    }

    if(((string)document["Actors"].GetString()).compare("N/A")){
        for(string& s: (SplitString(document["Actors"].GetString(), true, ','))){
            result.push_back(s);
        }
    }

    return result;
}

double GetMovieImdbRating(string json, int minVotes){
    int imdbVotes = 0;

    Document document;
    document.Parse(json.c_str());

    if(((string)document["imdbRating"].GetString()).compare("N/A") && ((string)document["imdbVotes"].GetString()).compare("N/A")){
        imdbVotes = stoi(RemoveComma(document["imdbVotes"].GetString()));
    }

    if(imdbVotes >= minVotes){
        return stod(document["imdbRating"].GetString());
    } else {
        return -1.0;
    }
}

int GetMovieYear(string json){
    Document document;
    document.Parse(json.c_str());

    if(!((string)document["Year"].GetString()).compare("N/A")){
        return -1;
    } else {
        return stoi(document["Year"].GetString());
    }
}

bool GetMovieResponse(string json){
    Document document;
    document.Parse(json.c_str());

    if(!((string)document["Response"].GetString()).compare("True")){
        return true;
    } else {
        return false;
    }
}

bool GetMovieAwards(string json){
    Document document;
    document.Parse(json.c_str());

    if(!((string)document["Awards"].GetString()).compare("N/A")){
        return false;
    } else {
        return true;
    }
}
