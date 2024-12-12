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
    int duration; // Duration in seconds
    char genre[GENREMAXLENGTH];
    double rating;
    char actor[ACTORSMAXLENGTH];
    double score;
} movieData;

typedef struct pref
{
    char genre1[GENREMAXLENGTH];
    char actor[ACTORSMAXLENGTH];
    int timetowatch; // Time in seconds
} pref;

// Function Prototype
void give_points(movieData movieArray[], int size, pref userpref);

int main(void)
{
    pref userpref;

    // User Input
    printf("Input genre: \n");
    scanf(" %s", userpref.genre1);

    printf("Input actor: \n");
    scanf(" %[^\n]s", userpref.actor);

    printf("Input available time to watch (in minutes): \n");
    scanf("%d", &userpref.timetowatch);
    userpref.timetowatch *= 60; // Convert to seconds

    // Movie Array Initialization
    movieData movieArray[3] = {
        {"Star Wars", "16", 140 * 60, "Adventure", 9.9, "Ewan McGregor", 0},
        {"Wall-E", "6", 85 * 60, "Adventure", 9.2, "Elissa Knight", 0},
        {"Scary Movie", "18", 90 * 60, "Horror", 8.7, "Anna Faris", 0}};

    // Call the function to evaluate scores
    give_points(movieArray, 3, userpref);

    // Output Movies with Scores
    printf("\nMovies with their scores:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Title: %s, Score: %.2f\n", movieArray[i].title, movieArray[i].score);
    }

    return 0;
}

void give_points(movieData movieArray[], int size, pref userpref)
{
    for (int i = 0; i < size; i++) // Loop through movies
    {
        // Compare Actor
        if (strcmp(movieArray[i].actor, userpref.actor) == 0)
        {
            movieArray[i].score += 1;
        }

        // Compare Genre
        if (strcmp(movieArray[i].genre, userpref.genre1) == 0)
        {
            movieArray[i].score += 1;
        }

        // Compare Duration (absolute difference)
        int timeDiff = abs(userpref.timetowatch - movieArray[i].duration);
        if (timeDiff <= 300) // Difference <= 5 minutes
        {
            movieArray[i].score += 3;
        }
        else if (timeDiff <= 600) // Difference <= 10 minutes
        {
            movieArray[i].score += 2;
        }
        else if (timeDiff <= 900) // Difference <= 15 minutes
        {
            movieArray[i].score += 1;
        }
    }
}
