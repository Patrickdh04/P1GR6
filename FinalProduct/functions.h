// Header file
#define NAMEMAXLENGTH 100
#define GENREMAXLENGTH 12
#define AGERATINGMAXLENGTH 10
#define MAXDURATION 4
#define MAXAMOUNTOFGENRES 3
#define MAXAMOUNTOFACTORS 4
#define ACTORSMAXLENGTH 50
#define MOVIESTOTAL 9957
#define TIMEMAXLENGTH 4
#define YEARMAXLENGTH 13
#define MULTIPLEGENRESMAXLENGTH 500
#define MULTIPLEACTORSMAXLENGTH 1000
#define DURATIONMAXLENGTH 10

struct pref
{
    char genres[MAXAMOUNTOFGENRES][GENREMAXLENGTH];
    int genrepref1;
    int genrepref2;
    int genrepref3;
    char actors[MAXAMOUNTOFACTORS][ACTORSMAXLENGTH];
    int min;
    int max;
    int timetowatch;
    char ageRating;
};

struct conpref
{
    char seriesName[50];
    int timetowatch;
};

struct movieData
{
    char title[NAMEMAXLENGTH];
    int isSeries;
    char ageRating[AGERATINGMAXLENGTH];
    int duration;
    char genre[MAXAMOUNTOFGENRES][GENREMAXLENGTH];
    double rating;
    char actor[MAXAMOUNTOFACTORS][ACTORSMAXLENGTH];
    int episodes;
    int score;
};

int profileMain();
void setTimeSetting(int *timeSettingChosen);
void startWarning(int choice, char nc, int newMovieTime, int conWatchTime);
int inputMain(char *nc, struct pref *newMovie, struct conpref *conWatch);
int movieSortMain(char nc, struct pref *newMovie, struct conpref *conWatch, struct movieData *movies, struct movieData *series, int *sizeOfMovies, int *sizeOfSeries, struct movieData *conWatchData);
int moviePointsMain(struct movieData *movies, struct movieData *series, struct pref newMovie, int *sizeOfMovies, int *sizeOfSeries, char nc, struct movieData *conWatchData, struct conpref conWatch);