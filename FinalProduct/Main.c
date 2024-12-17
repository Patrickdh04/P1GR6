#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct pref pref;
typedef struct conpref conpref;
typedef struct movieData movieData;

int main(void){
    char nc = '?';
    pref newMovie;
    conpref conWatch;
    movieData conWatchData;
    inputMain(&nc, &newMovie, &conWatch);
    
    movieData *movies = malloc(MOVIESTOTAL * sizeof(movieData));
    movieData *series = malloc(MOVIESTOTAL * sizeof(movieData));

    int sizeOfMovies = 0, sizeOfSeries = 0;
    movieSortMain(nc, &newMovie, &conWatch, movies, series, &sizeOfMovies, &sizeOfSeries, &conWatchData);

    moviePointsMain(movies, series, newMovie, &sizeOfMovies, &sizeOfSeries, nc, &conWatchData, conWatch);

    free(movies);
    free(series);


    return 0;
}
