using namespace std;

typedef struct sm {
  int rate;
  double similarity;
} SimilarityResume;

typedef map<string,int> View;
typedef map<string, View> MovieList;
typedef map<string, View> UserList;

void GetRatings(string filename, MovieList *movies, UserList *users);
void SetPredictions(string filename, MovieList *movies, UserList *users);
