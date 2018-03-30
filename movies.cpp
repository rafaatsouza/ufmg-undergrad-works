#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "movies.h"

using namespace std;

MovieList GetRatings(string filename){
  MovieList movies;
  int count = 0;
  string::size_type size;
  ifstream file(filename.c_str());
  string line = "";

	while (getline(file, line)) {
    if(count > 0){
      string itemId;
      View v;
      int firstCommaPosition = line.find(",");
      int dotsPosition = line.find(":");

      itemId = line.substr(dotsPosition + 1, firstCommaPosition - dotsPosition - 1);
      v.user = line.substr(0,dotsPosition);
      v.rate = stoi(line.substr(firstCommaPosition + 1, 1),&size);

      if(movies.find(itemId) != movies.end()) {
        movies[itemId].push_back(v);
      }
      else {
        vector<View> vv;
        vv.push_back(v);

        movies[itemId] = vv;
      }

    }
    count++;
  }

  return movies;
}
