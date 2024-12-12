#include "CoolName.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define MAXDURATION 4
#define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENGTH 200
typedef struct movieData
{
    char title[NAMEMAXLENGTH];
    char ageRating[AGERATINGMAXLENGTH];
    char duration[MAXDURATION];
    char genre[GENREMAXLENGTH];
    double rating;
    char actors[ACTORSMAXLENGTH];
} movieData;

int almostmain(void)
{
    movieData m1 = {"star wars", 16, 140 * 60, "Adventure", 9.9, "Ewan McGregor"};
    movieData m2 = {"wall-e", 6, 85 * 60, "Adventure", 9.2, "Elissa Knight"};
    movieData m3 = {"scary movie", 18, 90 * 60, "Horror", 8.7, "Anna Faris"};
}

void give_points(movieData)
{
  
}