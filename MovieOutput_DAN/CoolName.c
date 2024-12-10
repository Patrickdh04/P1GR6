#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
// #define MAXDURATION 4
// #define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENGTH 200

typedef struct movieData
{
  char title[NAMEMAXLENGTH];
  char ageRating[AGERATINGMAXLENGTH];
  int duration;
  char genre[GENREMAXLENGTH];
  double rating;
  char actor[ACTORSMAXLENGTH];
  int score;
} movieData;
typedef struct seriesData
{
  char title[NAMEMAXLENGTH];
  char ageRating[AGERATINGMAXLENGTH];
  int duration;
  char genre[GENREMAXLENGTH];
  double rating;
  char actor[ACTORSMAXLENGTH];
  int score; 
} seriesData;


typedef struct pref
{
  char genre1[GENREMAXLENGTH];
  int genrepref1;
  char genre2[GENREMAXLENGTH];
  int genrepref2;
  char genre3[GENREMAXLENGTH];
  int genrepref3;
  char actor1[ACTORSMAXLENGTH];
  char actor2[ACTORSMAXLENGTH];
  char actor3[ACTORSMAXLENGTH];
  int timetowatch;
  char ageRating;
} pref;

// Prototypes
void give_points(movieData movieArray[], pref userpref, int size);
void give_points_series(seriesData seriesArray[], pref userpref, int size);
int sort_movie(const void *a, const void *b);
int sort_series(const void *a, const void *b);

int main(void)

{
  pref userpref;

  printf("Input genre: \n");
  scanf(" %s", userpref.genre1);

  printf("Input actor: \n");
  scanf(" %[^\n]s", userpref.actor1);

  printf("Input time watch: \n");
  scanf(" %d", &userpref.timetowatch);
  userpref.timetowatch *= 60;

  movieData movieArray[3] =
      {
          {"star wars", "16", 8400, "Adventure", 9.8, "Ewan McGregor", 0},
          {"wall-e", "6", 5100, "Adventure", 9.2, "Elissa Knight", 0},
          {"scary movie", "18", 5400, "Horror", 8.7, "Anna Faris", 0}};
  seriesData seriesArray[3] = 
      {
       {"stranger things", "16", 2400, "horror", 8.2, "Elleven", 0},
       {"Arcane", "13", 2000, "Animation", 10, "Ella", 0},
       {"Invincible", "18", 1600, "Action", 8.3, "Big Guy", 0}};


int size_movie = sizeof(movieArray) / sizeof(movieArray[0]);
int size_series = sizeof(seriesArray) / sizeof(seriesArray[0]);

// give points to movies and series
give_points(movieArray, userpref, size_movie);
give_points_series(seriesArray, userpref, size_series);

// sort points for movies and series
qsort(movieArray, size_movie, sizeof(movieData), sort_movie);
qsort(seriesArray, size_series, sizeof(seriesData), sort_series);

//display movie
printf("These are the movie recommendations: \n");
printf("%-16s%-16s%-16s%-16s%-16s%-16s\n", "Title:", "Genre:", "Actor:", "Duration:", "IMDB:", "TEST-SCORE");
printf("-------------------------------------------------------------------------------------------\n");
for (int i = 0; i < size_movie; i++)
{
  printf("%-16s%-16s%-16s%-16d%-16.1lf%-16d\n", movieArray[i].title, movieArray[i].genre, movieArray[i].actor, movieArray[i].duration / 60, movieArray[i].rating, movieArray[i].score);
}
// display serie
printf("\nThese are the serie recommendations: \n");
printf("%-16s%-16s%-16s%-16s%-16s%-16s\n", "Title:", "Genre:", "Actor:", "Duration:", "IMDB:", "TEST-SCORE");
printf("-------------------------------------------------------------------------------------------\n");

for (int i = 0; i < size_series; i++)
{
  printf("%-16s%-16s%-16s%-16d%-16.1lf%-16d\n", seriesArray[i].title, seriesArray[i].genre, seriesArray[i].actor, seriesArray[i].duration / 60, seriesArray[i].rating, seriesArray[i].score);  
}
return 0;
}

void give_points(movieData movieArray[], pref userpref, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (strcmp(movieArray[i].actor, userpref.actor1) == 0)
    {
      movieArray[i].score += 1;
    }
    if (strcmp(movieArray[i].genre, userpref.genre1)== 0)
    {
      movieArray[i].score += 1;
    }
    //points according to time-to-watch
    int timeDiff = userpref.timetowatch - movieArray[i].duration;
    if (timeDiff<= 300)
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
    if (strcmp(seriesArray[i].actor, userpref.actor1) == 0)
    {
      seriesArray[i].score += 1;
    }
    if (strcmp(seriesArray[i].genre, userpref.genre1)== 0)
    {
      seriesArray[i].score += 1;
    }
    //points according to time-to-watch
    int timeDiff = userpref.timetowatch - seriesArray[i].duration;
    if (timeDiff<= 300)
    {
      seriesArray[i].score += 3;
    }
    else if (timeDiff <= 600)
    {
      seriesArray[i].score += 2;
    }
    else if (timeDiff <= 900)
    {
      seriesArray[i].score += 1;
    }
  }
}

/*int sort_movie(const void *a, const void *b)
{
    const movieData *movieA = (const movieData *)a;
    const movieData *movieB = (const movieData *)b;

    // Sort primarily by score (descending order)
    if (movieB->score != movieA->score) 
    {
        return movieB->score - movieA->score;
    }
    return movieA->duration - movieB->duration;
}*/

/*int sort_series(const void *a, const void *b)
{
    const seriesData *seriesA = (const seriesData *)a;
    const seriesData *seriesB = (const seriesData *)b;

    // Sort primarily by score 
    if (seriesB->score != seriesA->score) 
    {
        return seriesB->score - seriesA->score;
    }
    // Sort IMDB Score
    int rating_diff_a = *seriesA->rating - seriesA-> rating;
    int rating_diff_b = *seriesB->rating - seriesB-> rating;
    return rating_diff_b - rating_diff_a;
}*/

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
