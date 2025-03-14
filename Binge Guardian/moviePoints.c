#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct movieData movieData;
typedef struct pref pref;
typedef struct conpref conpref;

// Prototypes
void give_points_movies(movieData movies[], pref newMovie, int size);
void give_points_series(movieData series[], pref newMovie, int size);
int sort_movie(const void *a, const void *b);
int sort_series(const void *a, const void *b);
void display(movieData *movies, int moviesLength, movieData *series, int seriesLength, int currentMovieIndex);
void displayContinue(movieData *conWatchData);

int moviePointsMain(movieData *movies, movieData *series, pref newMovie, int *sizeOfMovies, int *sizeOfSeries, char nc, movieData *conWatchData, conpref conWatch)
{
  if (nc == 'n')
  {
    int seriesLength = *sizeOfSeries;
    int moviesLength = *sizeOfMovies;

    for (int i = 0; i < seriesLength; i++)
    {
      if (series[i].duration > 0) // Ensure division is valid
      {
        series[i].episodes = newMovie.timetowatch / series[i].duration;
      }
    }
    // give points to movies and series
    give_points_movies(movies, newMovie, moviesLength);
    give_points_series(series, newMovie, seriesLength);
    // sort points for movies and series
    qsort(movies, moviesLength, sizeof(movieData), sort_movie);
    qsort(series, seriesLength, sizeof(movieData), sort_series);
    display(movies, moviesLength, series, seriesLength, 0);
  }
  else if (nc == 'c')
  {
    conWatchData->episodes = conWatch.timetowatch / conWatchData->duration;
    displayContinue(conWatchData);
  }
  else
  {
    printf("Error");
  }

  return 0;
}
// Points for movies
void give_points_movies(movieData movies[], pref newMovie, int size)
{
  for (int i = 0; i < size; i++)
  {
    movies[i].score = 0;

    int genreMatched[3] = {0, 0, 0}; // Track if a user genre has been matched
    // Check for genre matches
    for (int k = 0; k < 3 && movies[i].genre[k] != NULL; k++)
    {
      for (int j = 0; j < 3 && newMovie.genres[j] != NULL; j++)
      {
        if (!genreMatched[j] && strcmp(movies[i].genre[k], newMovie.genres[j]) == 0)
        {
          movies[i].score++;
          genreMatched[j] = 1;
          break;
        }
      }
    }
    int actorMatched[3] = {0, 0, 0}; // Track if a user actor has been matched
    // check for actor matches
    for (int l = 0; l < 3 && movies[i].actor[l] != NULL; l++)
    {
      for (int j = 0; j < 3 && newMovie.actors[j] != NULL; j++)
      {
        if (!actorMatched[j] && strcmp(movies[i].actor[l], newMovie.actors[j]) == 0)
        {
          movies[i].score += 3;
          actorMatched[j] = 1;
          break;
        }
      }
    }
    // Points based on time-to-watch
    int timeDiff = newMovie.timetowatch * 60 - movies[i].duration;
    if (timeDiff <= 300)
    {
      movies[i].score += 5;
    }
    else if (timeDiff <= 600)
    {
      movies[i].score += 3;
    }
    else if (timeDiff <= 900)
    {
      movies[i].score += 1;
    }
  }
}
// Points for series
void give_points_series(movieData series[], pref newMovie, int size)
{
  for (int i = 0; i < size; i++)
  {
    series[i].score = 0;
    int genreMatched[3] = {0, 0, 0}; // Track if a user genre has been matched
    // Check for genre matches
    for (int k = 0; k < 3 && series[i].genre[k] != NULL; k++)
    {
      for (int j = 0; j < 3 && newMovie.genres[j] != NULL; j++)
      {
        if (strcmp(series[i].genre[k], newMovie.genres[j]) == 0)
        {
          series[i].score++;
          genreMatched[j] = 1;
        }
      }
    }
    int actorMatched[3] = {0, 0, 0}; // Track if a user actor has been matched
    // check for actor matches
    for (int l = 0; l < 3 && series[i].actor[l] != NULL; l++)
    {
      for (int j = 0; j < 3 && newMovie.actors[j] != NULL; j++)
      {
        if (strcmp(series[i].actor[l], newMovie.actors[j]) == 0)
        {
          series[i].score += 3;
          actorMatched[j] = 1;
        }
      }
    }
  }
}
int sort_movie(const void *a, const void *b)
{
  const movieData *movieA = (const movieData *)a;
  const movieData *movieB = (const movieData *)b;
  // Sort primarily by score
  if (movieB->score != movieA->score)
  {
    return movieB->score - movieA->score;
  }
  // Sort by rating (IMDB score) if score is equal
  if (movieB->rating > movieA->rating)
  {
    return 1;
  }
  else if (movieB->rating < movieA->rating)
  {
    return -1;
  }
  return 0; // Equal score and rating
}
int sort_series(const void *a, const void *b)
{
  const movieData *seriesA = (const movieData *)a;
  const movieData *seriesB = (const movieData *)b;
  // Sort primarily by score
  if (seriesB->score != seriesA->score)
  {
    return seriesB->score - seriesA->score;
  }
  // Sort by rating (IMDB score) if score is equal
  if (seriesB->rating > seriesA->rating)
  {
    return 1;
  }
  else if (seriesB->rating < seriesA->rating)
  {
    return -1;
  }
  return 0; // Equal score and rating
}
void display(movieData *movies, int moviesLength, movieData *series, int seriesLength, int currentMovieIndex)
{
  int listSize = 5; // Number of items to show per page

  // display movie
  printf("These are the movie recommendations: \n\n");
  printf("%-35s%-16s%-16s\n", "Title:", "Duration:", "IMDB:");
  printf("-----------------------------------------------------------------------------");

  if (moviesLength - currentMovieIndex < 5)
  {
    for (int i = 0; i < moviesLength; i++)
    {
      printf("\n%-35.30s%-3d min         %-16.1lf",
             movies[i].title,
             movies[i].duration / 60,
             movies[i].rating);
    }
  }
  else
  {
    for (int i = 0 + currentMovieIndex; i < 5 + currentMovieIndex; i++)
    {
      printf("\n%-35.30s%-3d min         %-16.1lf",
             movies[i].title,
             movies[i].duration / 60,
             movies[i].rating);
    }
  }

  // display serie
  printf("\n\nThese are the series recommendations: \n\n");
  printf("%-35s%-16s%-16s%-16s\n", "Title:", "Duration:", "IMDB:", "Episodes:");
  printf("-----------------------------------------------------------------------------\n");
  if (seriesLength - currentMovieIndex < 5)
  {
    for (int i = 0; i < seriesLength; i++)
    {
      printf("%-35.30s%-3d min         %-16.1lf%-16d\n",
             series[i].title, series[i].duration / 60,
             series[i].rating, series[i].episodes);
    }
  }
  else
  {
    for (int i = 0 + currentMovieIndex; i < 5 + currentMovieIndex; i++)
    {
      printf("%-35.30s%-3d min         %-16.1lf%-16d\n",
             series[i].title, series[i].duration / 60,
             series[i].rating, series[i].episodes);
    }
  }

  char newRecChoice;
  printf("\nDo you want 5 new recommendations?\nType 'y' for yes, and anything else if you have something to watch.\n");
  scanf(" %c", &newRecChoice);

  if (newRecChoice == 'y')
  {
    display(movies, moviesLength, series, seriesLength, currentMovieIndex + listSize);
  }
}
void displayContinue(movieData *conWatchData)
{
  printf("%-35s%-16s%-16s%-16s\n", "Title:", "Duration:", "IMDB:", "Episodes:");
  printf("----------------------------------------------------------------------------------------------\n");
  printf("%-35.30s%-3d min         %-16.1lf%-16d\n", conWatchData->title, conWatchData->duration / 60, conWatchData->rating, conWatchData->episodes);
}
