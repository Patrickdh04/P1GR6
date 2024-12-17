#include "functions.h"

typedef struct pref pref;
typedef struct conpref conpref;

int main(void){
    char nc = '?';
    pref newMovie;
    conpref conWatch;
    inputMain(&nc, &newMovie, &conWatch);
    movieSortMain(nc, &newMovie, &conWatch);

    return 0;
}
