typedef struct v {
    char user[10];
    int rate;
} View;

typedef struct m {
    std::vector<View*> h;
    char id[10];
} Movie;

Movie* getsMovie(std::vector<Movie*> ml, char id[10]);
void addsMovie(std::vector<Movie*> ml, char id[10]);
void addsView(Movie *m, char user[10], int rate);
void freeMovies(std::vector<Movie*> ml);
