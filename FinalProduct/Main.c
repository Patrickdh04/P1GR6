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
    inputMain(&nc, &newMovie, &conWatch);
    printf("Con watch name: %s, New movie data. Genre1: %s, genre2: %s, genre3: %s, actor1: %s, actor2: %s, actor3: %s, time to watch: %i\n", conWatch.seriesName, newMovie.genre1, newMovie.genre2, newMovie.genre3, newMovie.actor1, newMovie.actor2, newMovie.actor3, newMovie.timetowatch);
    
    movieData *movies = malloc(MOVIESTOTAL * sizeof(movieData));
    movieData *series = malloc(MOVIESTOTAL * sizeof(movieData));

    movieSortMain(nc, &newMovie, &conWatch, movies, series);

    return 0;
}
