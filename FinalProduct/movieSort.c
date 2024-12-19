#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct movieData movieData;
typedef struct pref pref;
typedef struct conpref conpref;

// Prototypes
void saveMovieData(movieData *moviesPreSort);
void discard(movieData *movieToDiscard);
void sortMovies(movieData *moviesPreSort, movieData *movies, movieData *series, char nc, pref newMovie,
                char *conWatch, movieData *conWatchData, int *sizeOfMovies, int *sizeOfSeries);
void copyData(movieData *movieArray, int index, movieData *moviesPreSort, int indexPreSort);

int movieSortMain(char nc, pref *newMovie, conpref *conWatch, movieData *movies, movieData *series, int *sizeOfMovies, int *sizeOfSeries, movieData *conWatchData)
{
    // As a lot of data has to be stored, we will save it using dynamic memory allocation
    movieData *moviesPreSort = malloc(MOVIESTOTAL * sizeof(movieData));

    pref newMovieValue = *newMovie;

    // Check if memory allocation is successful
    if (moviesPreSort == NULL || movies == NULL || series == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    saveMovieData(moviesPreSort);
    sortMovies(moviesPreSort, movies, series, nc, newMovieValue, conWatch->seriesName, conWatchData, sizeOfMovies, sizeOfSeries);
    free(moviesPreSort);

    return 0;
}

void saveMovieData(movieData *moviesPreSort)
{
    // To determine if a movie is a series or not, we will look at if its release date has a "-" in the name after the number
    // This would suggest that a movie is released over the course of more than a year, which is only possible for tv-series
    // We therefore save the year information in a string, which we will later use to determine if a movie is a series or not
    char year[YEARMAXLENGTH];
    // We save all genres in one string to begin with, as the amount of genres varies between the data. The same applies to actors
    char genres[MULTIPLEGENRESMAXLENGTH];
    char actors[MULTIPLEACTORSMAXLENGTH];
    FILE *pFile = fopen("movies.csv", "r");

    if (pFile == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < MOVIESTOTAL; i++)
    {
        char stringduration[DURATIONMAXLENGTH] = "0";
        // As all data is split up via comma, any movie with a comma in its name has the name in between "|"
        // We therefore check for this so that those movies' data do not become invalid
        char commaInNameCheck[NAMEMAXLENGTH] = "0";
        fscanf(pFile, " %c", commaInNameCheck);
        if (commaInNameCheck[0] == '|')
        {
            fscanf(pFile, " %99[^|]|,", moviesPreSort[i].title);
        }
        else
        {
            fscanf(pFile, " %99[^,],", moviesPreSort[i].title);
            strcat(commaInNameCheck, moviesPreSort[i].title);
            strcpy(moviesPreSort[i].title, commaInNameCheck);
        }

        fscanf(pFile, " %12[^,], %9[^,], %9[^,],", year, moviesPreSort[i].ageRating,
               stringduration);

        // Agerating is translated to 'y' if they have adult rating (TV-MA) and 'n' if movie does not have adult rating
        if (strcmp(moviesPreSort[i].ageRating, "TV-MA") == 0)
        {
            strcpy(moviesPreSort[i].ageRating, "y");
        }
        else
        {
            strcpy(moviesPreSort[i].ageRating, "n");
        }

                // If there is a valid duration we save the data, if not we discard the movie
        if (stringduration[0] != '0')
        {
            sscanf(stringduration, "%i", &moviesPreSort[i].duration);
            // We convert duration from minutes to seconds
            moviesPreSort[i].duration *= 60;
        }
        else
        {
            fscanf(pFile, " %*[^\n]");
            discard(&moviesPreSort[i]);
            continue;
        }
        // We check if a movie is a series
        if (year[5] == '-' || moviesPreSort[i].duration < 3000)
        {
            moviesPreSort[i].isSeries = 1;
        }
        // Before we continue saving data we need to determine if there are multiple genres or not
        // If there are more than one, the genres will be listed within this "|" symbol
        // If there is just one, the genre data will just be between comma like the rest of the data
        char multipleGenreCheck[GENREMAXLENGTH] = "0";
        fscanf(pFile, " %c", multipleGenreCheck);
        // As we need to save a value on all 3 genre variables of the struct, we will start by manually saving a value
        // indicating that it is empty
        for (int l = 0; l < MAXAMOUNTOFGENRES; l++)
        {
            strcpy(moviesPreSort[i].genre[l], "0");
        }

        if (multipleGenreCheck[0] == '|')
        {
            fscanf(pFile, " %499[^|]|,", genres);
            // We save each genre
            sscanf(genres, " %19[^,], %19[^,], %19[^,]", moviesPreSort[i].genre[0],
                   moviesPreSort[i].genre[1], moviesPreSort[i].genre[2]);
        }
        else if (multipleGenreCheck[0] != ',')
        {
            fscanf(pFile, "%99[^,],", moviesPreSort[i].genre[0]);
            strcat(multipleGenreCheck, moviesPreSort[i].genre[0]);
            strcpy(moviesPreSort[i].genre[0], multipleGenreCheck);
        }

        // In the same way we check if there are multiple genres, we will check if a rating is listed
        // If there is no rating, the movie will be discarded, as rating is a criteria we use when recommending later
        char ratingCheck[4];
        fscanf(pFile, " %c", ratingCheck);
        if (ratingCheck[0] == ',')
        {
            fscanf(pFile, " %*[^\n]");
            discard(&moviesPreSort[i]);
            continue;
        }
        fscanf(pFile, " %2[^,],", &ratingCheck[1]);
        sscanf(ratingCheck, "%lf", &moviesPreSort[i].rating);

        // The last data we need to scan from the dataset is actors
        // As we have no way of knowing how many actors that are listed we make sure to fill in "0" so we wont have
        // unpredictable behaviour when using the actor data
        for (int r = 0; r < MAXAMOUNTOFACTORS; r++)
        {
            strcpy(moviesPreSort[i].actor[r], "0");
        }

        // As some movies have directors listed, we first check if there is an director
        // Directors are listed with a ' before the next comma, which allows to differentiate between directors and actors
        fscanf(pFile, " %*[^[][%c", &moviesPreSort[i].actor[0][0]);
        if (moviesPreSort[i].actor[0][0] == ']')
        { // No actors are present. Rewrite actor 1 to '0'
            moviesPreSort[i].actor[0][0] = '0';
        }
        else
        {
            fscanf(pFile, " %999[^]],", actors);
            if (strrchr(actors, '~') != NULL)
            {
                sscanf(actors, " %*[^:]:\", \"%49[^\"]\"", moviesPreSort[i].actor[0]);
                sscanf(actors, " %*[^:]:\", \"%*[^\"]\"%999[^]]", actors);
            }
            else
            {
                sscanf(actors, " %49[^\"]\"", moviesPreSort[i].actor[0]);
                sscanf(actors, " %*[^\"]\"%999[^]]", actors);
            }
            // Save remaining actors (if there are any)
            sscanf(actors, ",\"%49[^\"]\",\"%49[^\"]\",\"%49[^\"]\"", moviesPreSort[i].actor[1],
                   moviesPreSort[i].actor[2], moviesPreSort[i].actor[3]);
        }

        /* printf("title %i: %s, age: %s, dur: %i, g1: %s, g2: %s, g3: %s, isSer: %i, rati: %.1lf\nAc1:%s, Ac2: %s, Ac3: %s, Ac4: %s\n\n",
                i, moviesPreSort[i].title, moviesPreSort[i].ageRating, moviesPreSort[i].duration, moviesPreSort[i].genre[0],
                moviesPreSort[i].genre[1], moviesPreSort[i].genre[2], moviesPreSort[i].isSeries, moviesPreSort[i].rating,
                moviesPreSort[i].actor[0], moviesPreSort[i].actor[1], moviesPreSort[i].actor[2], moviesPreSort[i].actor[3]);*/

        fscanf(pFile, "%*[^\n]");
    }
    fclose(pFile);
    return;
}

void discard(movieData *movieToDiscard)
{
    // By setting the data of a movie to "0" we can deem it as discarded and ignore it later when recommending movies
    strcpy(movieToDiscard->title, "0");
    movieToDiscard->isSeries = 0;
    strcpy(movieToDiscard->ageRating, "0");
    movieToDiscard->duration = 0;
    strcpy(movieToDiscard->genre[0], "0");
    strcpy(movieToDiscard->genre[1], "0");
    strcpy(movieToDiscard->genre[2], "0");
    movieToDiscard->rating = 0;
    strcpy(movieToDiscard->actor[0], "0");
    strcpy(movieToDiscard->actor[1], "0");
    strcpy(movieToDiscard->actor[2], "0");
    strcpy(movieToDiscard->actor[3], "0");
}

void sortMovies(movieData *moviesPreSort, movieData *movies, movieData *series, char nc, pref newMovie,
                char *conWatch, movieData *conWatchData, int *sizeOfMovies, int *sizeOfSeries)
{
    int isMovieCounter = 0, isSeriesCounter = 0;
    if (nc == 'n') // If user want a new recommendation
    {
        for (int i = 0; i < MOVIESTOTAL; i++)
        {
            // Check for search criteria
            for (int l = 0; l < MAXAMOUNTOFGENRES; l++)
            { // We check if movie match user's input
                if ((strcmp(moviesPreSort[i].genre[l], newMovie.genres[0]) == 0 ||
                     strcmp(moviesPreSort[i].genre[l], newMovie.genres[1]) == 0 ||
                     strcmp(moviesPreSort[i].genre[l], newMovie.genres[2]) == 0 ||
                     (newMovie.genres[0][0] == '\0' && newMovie.genres[1][0] == '\0' &&
                      newMovie.genres[2][0] == '\0')) &&
                    (moviesPreSort[i].ageRating[0] == newMovie.ageRating || moviesPreSort[i].ageRating[0] == 'n') &&
                    (moviesPreSort[i].rating >= newMovie.min && moviesPreSort[i].rating <= newMovie.max) &&
                    moviesPreSort[i].duration <= newMovie.timetowatch)
                {
                    if (moviesPreSort[i].isSeries)
                    {
                        copyData(series, isSeriesCounter, moviesPreSort, i);
                        isSeriesCounter++;
                        break;
                    }
                    else
                    {
                        copyData(movies, isMovieCounter, moviesPreSort, i);
                        isMovieCounter++;
                        break;
                    }
                }
            }
        }
    }
    else if (nc == 'c') // If user continues watching the movie name will be searched for
    {
        for (int i = 0; i < MOVIESTOTAL; i++)
        {
            if (strcmp(moviesPreSort[i].title, conWatch) == 0)
            {
                // If movie/series is found, all information is saved in conWatchData
                copyData(conWatchData, 0, moviesPreSort, i);
                break;
            }
        }
    }
    else
    {
        printf("Error: No command was found");
        exit(EXIT_FAILURE);
    }

    *sizeOfSeries = isSeriesCounter;
    *sizeOfMovies = isMovieCounter;

    return;
}

void copyData(movieData *movieArray, int index, movieData *moviesPreSort, int indexPreSort)
{
    strcpy(movieArray[index].title, moviesPreSort[indexPreSort].title);

    movieArray[index].isSeries = moviesPreSort[indexPreSort].isSeries;

    strcpy(movieArray[index].ageRating, moviesPreSort[indexPreSort].ageRating);

    movieArray[index].duration = moviesPreSort[indexPreSort].duration;

    strcpy(movieArray[index].genre[0], moviesPreSort[indexPreSort].genre[0]);
    strcpy(movieArray[index].genre[1], moviesPreSort[indexPreSort].genre[1]);
    strcpy(movieArray[index].genre[2], moviesPreSort[indexPreSort].genre[2]);

    movieArray[index].rating = moviesPreSort[indexPreSort].rating;

    strcpy(movieArray[index].actor[0], moviesPreSort[indexPreSort].actor[0]);
    strcpy(movieArray[index].actor[1], moviesPreSort[indexPreSort].actor[1]);
    strcpy(movieArray[index].actor[2], moviesPreSort[indexPreSort].actor[2]);
    strcpy(movieArray[index].actor[3], moviesPreSort[indexPreSort].actor[3]);
}