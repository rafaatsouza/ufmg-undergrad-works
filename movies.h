using namespace std;

typedef map<string,double> Similarities;
typedef map<string,int> View;
typedef map<string,string> Information;

typedef struct mi {
  View views;
  double averageRate;
  long int sumProductRate;
  Similarities similarities;
  Information informations;
} MovieInfo;

typedef map<string, MovieInfo> MovieList;
typedef map<string, View> UserList;

void GetMoviesInfo(string ratingsFileName, MovieList *movies, UserList *users);
void SetPredictions(string filename, MovieList *movies, UserList *users);
