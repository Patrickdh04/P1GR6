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
    char genre1[10];
    int genrepref1;
    char genre2[10];
    int genrepref2;
    char genre3[10];
    int genrepref3;
    char actor1[50];
    char actor2[50];
    char actor3[50];
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
};

int inputMain(char *nc, struct pref *newMovie, struct conpref *conWatch);
int movieSortMain(char nc, struct pref *newMovie, struct conpref *conWatch);