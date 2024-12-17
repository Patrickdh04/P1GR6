#include "functions.h"
#include <stdio.h>

typedef struct pref pref;
typedef struct conpref conpref;

int main(void){
    char nc = '?';
    pref newMovie;
    conpref conWatch;
    inputMain(&nc, &newMovie, &conWatch);
    printf("New movie data. Genre1: %s, genre2: %s, genre3: %s, actor1: %s, actor2: %s, actor3: %s, time to watch: %i", newMovie.genre1, newMovie.genre2, newMovie.genre3, newMovie.actor1, newMovie.actor2, newMovie.actor3, newMovie.timetowatch);
    movieSortMain(nc, &newMovie, &conWatch);

    return 0;
}
