#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define ACTORSMAXLENGTH 200

typedef struct movieData movieData;
typedef struct pref pref;

// Prototypes
void give_points(movieData movieArray[], pref userpref, int size);
void give_points_series(seriesData seriesArray[], pref userpref, int size);
int sort_movie(const void *a, const void *b);
int sort_series(const void *a, const void *b);
void display(movieData movieArray[], int size_movie, seriesData seriesArray[], int size_series);
int main(void)
{
  pref userpref;
  for (int i = 0; i < 3; i++)
  {
    userpref.genres[i] = malloc(NAMEMAXLENGTH * sizeof(char)); // Allocate memory for each genre
    printf("Input genre %d: \n", i + 1);
    scanf(" %s", userpref.genres[i]);
  }
  for (int j = 0; j < 3; j++)
  {
    userpref.actors[j] = malloc(NAMEMAXLENGTH * sizeof(char)); // Allocate memory for each genre
    printf("Input actor %d: \n", j + 1);
    scanf(" %[^\n]s", userpref.actors[j]);
  }
  printf("Input time watch: \n");
  scanf(" %d", &userpref.timetowatch);
  userpref.timetowatch *= 60;
  movieData movieArray[3] =
      {
          {"Star wars", "16", 8400, {"Adventure", "Fantasy", "Sci-fi"}, 9.8, {"Ewan McGregor", "Mathias", "Patrick"}, 0},
          {"Wall-e", "6", 5100, {"Adventure", "Sci-fi", "Animation"}, 9.2, {"Elissa Knight", "Nikolaj", "Gabby"}, 0},
          {"Scary movie", "18", 5400, {"Horror", "Comedy", NULL}, 8.7, {"Anna Faris", "Dan", "Asker"}, 0}
      };
  seriesData seriesArray[3] =
      {
          {"stranger things", "16", 2400, {"Horror", "Adventure", NULL}, 8.2, {"Elleven", NULL, NULL}, 0, 0},
          {"Arcane", "13", 2000, {"Animation", NULL, NULL}, 10, {"Ella", "Joakim", NULL}, 0, 0},
          {"Invincible", "18", 1600, {"Action", NULL, NULL}, 8.3, {"Big Guy", NULL, NULL}, 0, 0}
      };
  int size_movie = sizeof(movieArray) / sizeof(movieArray[0]);
  int size_series = sizeof(seriesArray) / sizeof(seriesArray[0]);
  for (int i = 0; i < size_series; i++)
  {
    if (seriesArray[i].duration > 0) // Ensure division is valid
    {
      seriesArray[i].episodes = userpref.timetowatch / seriesArray[i].duration;
    }
    else
    {
      seriesArray[i].episodes + 0; // Handle cases where the series has no episodes
    }
  }
  // give points to movies and series
  give_points(movieArray, userpref, size_movie);
  give_points_series(seriesArray, userpref, size_series);
  // sort points for movies and series
  qsort(movieArray, size_movie, sizeof(movieData), sort_movie);
  qsort(seriesArray, size_series, sizeof(seriesData), sort_series);
  display(movieArray, size_movie, seriesArray, size_series);
  return 0;
}
//Points for movies
void give_points(movieData movieArray[], pref userpref, int size)
{
  for (int i = 0; i < size; i++)
  {
    int genreMatched[3] = {0, 0, 0}; // Track if a user genre has been matched
    // Check for genre matches
    for (int k = 0; k < 3 && movieArray[i].genres[k] != NULL; k++)
    {
      for (int j = 0; j < 3 && userpref.genres[j] != NULL; j++)
      {
        if (!genreMatched[j] && strcmp(movieArray[i].genres[k], userpref.genres[j]) == 0)
        {
          movieArray[i].score++;
          genreMatched[j] = 1;
          break;
        }
      }
    }
    int actorMatched[3] = {0, 0, 0}; // Track if a user actor has been matched
    // check for actor matches
    for (int l = 0; l < 3 && movieArray[i].actors[l] != NULL; l++)
    {
      for (int j = 0; j < 3 && userpref.actors[j] != NULL; j++)
      {
        if (!actorMatched[j] && strcmp(movieArray[i].actors[l], userpref.actors[j]) == 0)
        {
          movieArray[i].score++;
          actorMatched[j] = 1;
          break;
        }
      }
    }
    // Points based on time-to-watch
    int timeDiff = userpref.timetowatch * 60 - movieArray[i].duration;
    if (timeDiff <= 300)
    {
      movieArray[i].score += 3;
    }
    else if (timeDiff <= 600)
    {
      movieArray[i].score += 2;
    }
    else if (timeDiff <= 900)
    {
      movieArray[i].score += 1;
    }
  }
}
// Points for series
void give_points_series(seriesData seriesArray[], pref userpref, int size)
{
    for (int i = 0; i < size; i++)
    {
        int genreMatched[3] = {0, 0, 0}; // Track if a user genre has been matched
        // Check for genre matches
        for (int k = 0; k < 3 && seriesArray[i].genres[k] != NULL; k++)
        {
            for (int j = 0; j < 3 && userpref.genres[j] != NULL; j++)
            {
                if (strcmp(seriesArray[i].genres[k], userpref.genres[j]) == 0)
                {
                    seriesArray[i].score++;
                    genreMatched[j] = 1;
                }
            }
        }
        int actorMatched[3] = {0, 0, 0}; // Track if a user actor has been matched
        // check for actor matches
        for (int l = 0; l < 3 && seriesArray[i].actors[l] != NULL; l++)
        {
            for (int j = 0; j < 3 && userpref.actors[j] != NULL; j++)
            {
                if (strcmp(seriesArray[i].actors[l], userpref.actors[j]) == 0)
                {
                    seriesArray[i].score++;
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
  const seriesData *seriesA = (const seriesData *)a;
  const seriesData *seriesB = (const seriesData *)b;
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
void display(movieData movieArray[], int size_movie, seriesData seriesArray[], int size_series)
{
  // display movie
  printf("These are the movie recommendations: \n\n");
  printf("%-16s%-16s%-16s%-16s\n", "Title:", "Duration:", "IMDB:", "TEST-SCORE: "); // "TEST-SCORE" TEMPORARY
  printf("-----------------------------------------------------------");
  for (int i = 0; i < size_movie; i++)
  {
    printf("\n%-16s%-3d min         %-16.1lf%-16d",
           movieArray[i].title,
           movieArray[i].duration / 60,
           movieArray[i].rating,
           movieArray[i].score); // temporary
  }
  // display serie
  printf("\n\nThese are the series recommendations: \n\n");
  printf("%-16s%-16s%-16s%-16s%-16s\n", "Title:", "Duration:", "IMDB:", "Episodes:", "Test-Score");
  printf("-----------------------------------------------------------\n");
  for (int i = 0; i < size_series; i++)
  {
    printf("%-16s%-3d min         %-16.1lf%-16d%-16d\n",
           seriesArray[i].title, seriesArray[i].duration / 60,
           seriesArray[i].rating, seriesArray[i].episodes, seriesArray[i].score);
  }
}
