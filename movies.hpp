#include <vector>

using namespace std;

typedef map<string,double> Similarities;
typedef map<string,int> View;
typedef map<string,int> TermQuantity;

typedef struct mc {
  TermQuantity plot;
  int Year;
  std::vector<string> Genre, Country, Persons;
  bool Response;
} MovieContent;

typedef struct mi {
  View views;
  double averageRate;
  long int sumProductRate;
  Similarities similarities;
  MovieContent content;
} MovieInfo;

typedef map<string, MovieInfo> MovieList;
typedef map<string, View> UserList;

void GetMoviesInfo(string ratingsFileName, string contentFileName, MovieList *movies, UserList *users);
void SetPredictions(string filename, MovieList *movies, UserList *users);
