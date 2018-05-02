#include <vector>

using namespace std;

typedef map<string,double>::iterator simIterator;
typedef map<string,double> Similarities;

typedef map<string,int>::iterator viewIterator;
typedef map<string,int> View;

typedef map<string,int> TermQuantity;

typedef struct mc {
  TermQuantity plot;
  std::vector<string> Genre, Country, Persons;
  bool Response;
  double imdbRating;
} MovieContent;

typedef struct mi {
  View views;
  double averageRate;
  long int sumProductRate;
  Similarities simGenre, simCountry, simPerson;
  MovieContent content;
} MovieInfo;

typedef struct ui {
  View views;
  Similarities simGenre, simCountry, simPerson;
} UserInfo;

typedef map<string, MovieInfo> MovieList;
typedef map<string, UserInfo> UserList;

void GetMoviesInfo(string ratingsFileName, string contentFileName, MovieList *movies, UserList *users);
void SetPredictions(string filename, MovieList *movies, UserList *users);
