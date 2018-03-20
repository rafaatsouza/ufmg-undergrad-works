typedef struct m * tm_pont;

typedef struct v * tv_pont;

typedef struct v {
    char user[10];
    int rate;
    tv_pont prox;
} View;

typedef struct h {
    int countViews;
    tv_pont primeiro, ultimo;
} History;

typedef struct m {
    History *h;
    char id[10];
    tm_pont prox;
} Movie;

typedef struct ml {
    int countMovies;
    tm_pont primeiro, ultimo;
} MovieList;

MovieList* initMovieList();
Movie* getsMovie(MovieList *ml, char id[10]);
void addsMovie(MovieList *ml, char id[10]);
void addsView(Movie *m, char user[10], int rate);
void freeMovies(MovieList *ml);
void freeMovie(Movie *m);
