using namespace std;

typedef struct vu {
    string user;
    int rate;
} ViewByUser;

typedef struct vm {
    string movie;
    int rate;
} ViewByMovie;

typedef map<string, vector<ViewByUser> > MovieList;

typedef map<string, vector<ViewByMovie> > UserList;

void GetRatings(string filename, MovieList *movies, UserList *users);
