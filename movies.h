using namespace std;

typedef struct v {
    string user;
    int rate;
} View;

typedef map<string, vector<View> > MovieList;

MovieList GetRatings(string filename);
