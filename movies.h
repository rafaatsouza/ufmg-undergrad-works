using namespace std;

typedef map<string,double> Similarities;
typedef map<string,int> View;

typedef struct mi {
  View views;
  double averageRate;
  Similarities similarities;
} MovieInfo;

typedef struct ui {
  View views;
  double averageRate;
} UserInfo;

typedef map<string, MovieInfo> MovieList;
typedef map<string, UserInfo> UserList;

void GetRatings(string filename, MovieList *movies, UserList *users);
void SetPredictions(string filename, MovieList *movies, UserList *users);
