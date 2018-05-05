#include <string>
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
        for(string& s: (SplitStringByComma(document["Genre"].GetString(), false))){
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
        for(string& s: (SplitStringByComma(document["Country"].GetString(), false))){
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
        for(string& s: (SplitStringByComma(document["Language"].GetString(), false))){
            result.push_back(s);
        }
    }

    return result;
}

vector<string> GetMoviePersonVector(string json){
    Document document;
    document.Parse(json.c_str());
    vector<string> result;

    if(((string)document["Director"].GetString()).compare("N/A")){
        for(string& s: (SplitStringByComma(document["Director"].GetString(), true))){
            result.push_back(s);
        }
    }

    if(((string)document["Writer"].GetString()).compare("N/A")){
        for(string& s: (SplitStringByComma(document["Writer"].GetString(), true))){
            result.push_back(s);
        }
    }

    if(((string)document["Actors"].GetString()).compare("N/A")){
        for(string& s: (SplitStringByComma(document["Actors"].GetString(), true))){
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