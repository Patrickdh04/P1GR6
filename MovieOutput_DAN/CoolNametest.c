#include "CoolName.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define ACTORSMAXLENGTH 200

typedef struct movieData
{
  char title[NAMEMAXLENGTH];
  char ageRating[AGERATINGMAXLENGTH];
  int duration;
  char *genres[GENREMAXLENGTH];
  double rating;
  char actor[ACTORSMAXLENGTH];
  int score;
} movieData;

typedef struct seriesData
{
  char title[NAMEMAXLENGTH];
  char ageRating[AGERATINGMAXLENGTH];
  int duration;
  char *genres[GENREMAXLENGTH];
  double rating;
  char actor[ACTORSMAXLENGTH];
  int score;
  int episodes;
} seriesData;

typedef struct pref
{
  char *genres[GENREMAXLENGTH];
  int genrepref1;
  int genrepref2;
  int genrepref3;
  char actor1[ACTORSMAXLENGTH];
  char actor2[ACTORSMAXLENGTH];
  char actor3[ACTORSMAXLENGTH];
  int timetowatch;
  char ageRating;
} pref;

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
    userpref.genres[i] = malloc(NAMEMAXLENGTH * sizeof(char));
    printf("Input genre %d: \n", i + 1);
    scanf(" %s", userpref.genres[i]);
  }
  printf("Input actor: \n");
  scanf(" %[^\n]s", userpref.actor1);
  printf("Input time watch: \n");
  scanf(" %d", &userpref.timetowatch);
  userpref.timetowatch *= 60;
  
  movieData movieArray[3] =
      {
          {"Star wars", "16", 8400, {"Adventure", "Fantasy", "Sci-fi"}, 9.8, "Ewan McGregor", 0},
          {"Wall-e", "6", 5100, {"Adventure", "Sci-fi", "Animation"}, 9.2, "Elissa Knight", 0},
          {"Scary movie", "18", 5400, {"Horror", "Comedy", NULL}, 8.7, "Anna Faris", 0}};
  
  seriesData seriesArray[3] =
      {
          {"stranger things", "16", 2400, {"Horror", "Adventure", NULL}, 8.2, "Elleven", 0, 0},
          {"Arcane", "13", 2000, {"Animation", NULL, NULL}, 10, "Ella", 0, 0},
          {"Invincible", "18", 1600, {"Action", NULL, NULL}, 8.3, "Big Guy", 0, 0}};
  
  int size_movie = sizeof(movieArray) / sizeof(movieArray[0]);
  int size_series = sizeof(seriesArray) / sizeof(seriesArray[0]);
  
  for (int i = 0; i < size_series; i++)
  {
    if (seriesArray[i].duration > 0)
    {
      seriesArray[i].episodes = userpref.timetowatch / seriesArray[i].duration;
    }
    else
    {
      seriesArray[i].episodes + 0;
    }
  }

  give_points(movieArray, userpref, size_movie);
  give_points_series(seriesArray, userpref, size_series);
  
  qsort(movieArray, size_movie, sizeof(movieData), sort_movie);
  qsort(seriesArray, size_series, sizeof(seriesData), sort_series);
  
  display(movieArray, size_movie, seriesArray, size_series);
  return 0;
}

void give_points(movieData movieArray[], pref userpref, int size)
{
  for (int i = 0; i < size; i++)
  {
    int genreMatched[3] = {0, 0, 0};

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

    if (strcmp(movieArray[i].actor, userpref.actor1) == 0)
    {
      movieArray[i].score += 1;
    }

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

void give_points_series(seriesData seriesArray[], pref userpref, int size)
{
  for (int i = 0; i < size; i++)
  {
    int genreMatched[3] = {0, 0, 0};

    for (int k = 0; k < 3 && seriesArray[i].genres[k] != NULL; k++)
    {
      for (int j = 0; j < 3 && userpref.genres[j] != NULL; j++)
      {
        if (!genreMatched[j] && strcmp(seriesArray[i].genres[k], userpref.genres[j]) == 0)
        {
          seriesArray[i].score++;
          genreMatched[j] = 1;
          break;
        }
      }
    }

    if (strcmp(seriesArray[i].actor, userpref.actor1) == 0)
    {
      seriesArray[i].score += 1;
    }
  }
}

int sort_movie(const void *a, const void *b)
{
  const movieData *movieA = (const movieData *)a;
  const movieData *movieB = (const movieData *)b;

  if (movieB->score != movieA->score)
  {
    return movieB->score - movieA->score;
  }

  if (movieB->rating > movieA->rating)
  {
    return 1;
  }
  else if (movieB->rating < movieA->rating)
  {
    return -1;
  }
  return 0;
}

int sort_series(const void *a, const void *b)
{
  const seriesData *seriesA = (const seriesData *)a;
  const seriesData *seriesB = (const seriesData *)b;

  if (seriesB->score != seriesA->score)
  {
    return seriesB->score - seriesA->score;
  }

  if (seriesB->rating > seriesA->rating)
  {
    return 1;
  }
  else if (seriesB->rating < seriesA->rating)
  {
    return -1;
  }
  return 0;
}

void display(movieData movieArray[], int size_movie, seriesData seriesArray[], int size_series)
{
  printf("These are the movie recommendations: \n\n");
  printf("%-16s%-16s%-16s%-16s\n", "Title:", "Duration:", "IMDB:", "TEST-SCORE: ");
  printf("-----------------------------------------------------------");
  for (int i = 0; i < size_movie; i++)
  {
    printf("\n%-16s%-3d min         %-16.1lf%-16d",
           movieArray[i].title,
           movieArray[i].duration / 60,
           movieArray[i].rating,
           movieArray[i].score);
  }

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
