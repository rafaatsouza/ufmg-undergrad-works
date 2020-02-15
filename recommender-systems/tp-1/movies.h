using namespace std;

typedef map<string,double> Similarities;
typedef map<string,int> View;

typedef struct mi {
  View views;
  double averageRate;
  long int sumProductRate;
  Similarities similarities;
} MovieInfo;

typedef map<string, MovieInfo> MovieList;
typedef map<string, View> UserList;

void GetRatings(string filename, MovieList *movies, UserList *users);
void SetPredictions(string filename, MovieList *movies, UserList *users);
