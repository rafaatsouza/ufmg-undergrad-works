using namespace std;

vector<string> GetMovieGenreVector(string json);
vector<string> GetMovieCountryVector(string json);
vector<string> GetMovieLanguageVector(string json);
vector<string> GetMoviePersonVector(string json);
double GetMovieImdbRating(string json, int minVotes);
int GetMovieYear(string json);
bool GetMovieResponse(string json);
bool GetMovieAwards(string json);