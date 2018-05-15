#include <vector>

using namespace std;

typedef map<string,int>::iterator viewIterator;
typedef map<string,int> View;

typedef map<string,int> TermQuantity;
typedef map<string,int>::iterator TermQuantityIterator;

typedef struct mi {
  View views;
  TermQuantity Genre, Country, Language, Person, Plot;
  int Year;
  bool Response, hasAwardsWin;
  double imdbRating;
} MovieInfo;

typedef struct ui {
  View views;
  TermQuantity Genre, Country, Language, Person, Plot;
  int averageYear;
  double yearDeviation;
} UserInfo;

typedef map<string, MovieInfo> MovieList;
typedef map<string, UserInfo> UserList;

void GetMoviesInfo(string ratingsFileName, string contentFileName, MovieList *movies, UserList *users);
void PrintPredictions(string filename, MovieList *movies, UserList *users);
