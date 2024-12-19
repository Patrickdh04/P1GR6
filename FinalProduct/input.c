#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define AMOUNTOFGENRES 21

typedef struct pref pref;
typedef struct conpref conpref;

// Prototypes
pref new_rec(void);
conpref con_rec(void);
int getdiff(void);

int inputMain(char *nc, pref *newMovie, conpref *conWatch)
{
    pref movie;
    conpref conWatchMovie;
    char choice;
    do
    {
        // New recommendation or continue with series?
        printf("Do you want a new recommendation or continue watching a series? (n for new / c for continue): \n");

        scanf(" %c", &choice);
        while (getchar() != '\n')
            ;
    } while (choice != 'n' && choice != 'c'); // check if user typed n or c, repeat if not

    if (choice == 'n')
    {
        movie = new_rec(); // run new recommendation data collection
        *newMovie = movie;
    }
    else if (choice == 'c')
    {
        conWatchMovie = con_rec(); // run continue series data collection
        *conWatch = conWatchMovie;
    }
    else
    { // if somehow nc is not n or c
        printf("Problem with program, stopping...");
        exit(EXIT_FAILURE);
    }

    *nc = choice;

    return 0;
}

pref new_rec(void)
{

    int g1 = -1, g2 = -1, g3 = -1;                    // g1-2-3 default index -1
    char gp1[15] = "?", gp2[15] = "?", gp3[15] = "?"; // 3 genre preferences
    char actor1[50] = "?", actor2[50] = "?", actor3[50] = "?";
    char genre[AMOUNTOFGENRES][15] = {"Action", "Adventure", "Animation", "Biography", "Comedy", "Crime", "Documentary", "Drama", "Family",
                                      "Fantasy", "History", "Horror", "Musical", "Mystery", "Reality-TV", "Romance", "Sci-Fi", "Short", "Sport", "Thriller", "War"};

    char ar;

    int min_rating = 0, max_rating = 0;

    do
    { // Get 3 genres
        printf("\nWrite 1 genre you want to see (Write '?' for a list of genres): \n");

        scanf(" %s", gp1);

        for (int i = 0; i < AMOUNTOFGENRES; i++)
        {
            if (strcmp(gp1, genre[i]) == 0)
            {
                g1 = i;
            }
        }

        if (strcmp(gp1, "?") == 0)
        { // print list of genres
            printf("\nAction, Adventure, Animation, Biography, Comedy, Crime, Drama, Family, Fantasy, History, Horror, \nMusical, Mystery, Reality-TV, Romance, Sci-Fi, Short, Sport, Thriller, Documentary, War\n");
        }

    } while (g1 == -1); // repeat if no valid genre 1

    printf("\nWrite a second genre you want to see (Write '?' to skip): \n");

    scanf(" %s", gp2);

    printf("\nWrite a third genre you want to see (Write '?' to skip): \n");

    scanf(" %s", gp3);

    for (int i = 0; i < AMOUNTOFGENRES; i++)
    {
        if (strcmp(gp2, genre[i]) == 0)
        {
            g2 = i;
        }
        else if (strcmp(gp3, genre[i]) == 0)
        {
            g3 = i;
        } // Get the 21 genre indexes 0-20
    }

    printf("\nWrite 1 actor you want to see (Write '?' to skip): \n");

    scanf(" %[^\n]%*c", actor1);

    printf("\nWrite a second actor you want to see (Write '?' to skip): \n");

    scanf(" %[^\n]%*c", actor2);

    printf("\nWrite a third actor you want to see (Write '?' to skip): \n");

    scanf(" %[^\n]%*c", actor3);

    do
    {
        printf("\nDo you want to be recommended 18+ films? (y/n): \n");
        scanf(" %c", &ar);
        while (getchar() != '\n')
            ;
    } while (ar != 'y' && ar != 'n'); // repeat if no valid answer

    do
    {
        printf("\nWrite the minimum IMDb rating you want to look for (whole number between 1 and 9): \n");

        scanf(" %d", &min_rating);
    } while (min_rating < 0 || min_rating > 10); // repeat if not between 1 and 9

    do
    {
        printf("\nWrite the maximum IMDb rating you want to look for (whole number between 1 and 10): \n");

        scanf(" %d", &max_rating);
    } while (max_rating <= min_rating || max_rating > 10); // repeat if not bigger than min_rating and less than 10

    int diff = getdiff(); // get time diff in seconds

    pref preference;
    // create struct of data
    strcpy(preference.genres[0], genre[g1]);
    preference.genrepref1 = g1;
    strcpy(preference.genres[1], genre[g2]);
    preference.genrepref2 = g2;
    strcpy(preference.genres[2], genre[g3]);
    preference.genrepref3 = g3;

    strcpy(preference.actors[0], actor1);
    strcpy(preference.actors[1], actor2);
    strcpy(preference.actors[2], actor3);

    preference.min = min_rating;
    preference.max = max_rating;

    preference.timetowatch = diff;

    preference.ageRating = ar;

    return preference;
}

conpref con_rec(void)
{
    char seriesName[50] = "?";
    do
    { // Get series name
        printf("\nWrite the name of the series: \n");
        scanf("%[^\n]%*c", seriesName);

    } while (strcmp(seriesName, "?") == 0);

    int diff = getdiff(); // Get time diff in seconds

    conpref con_series;
    // create struct of data
    strcpy(con_series.seriesName, seriesName);
    con_series.timetowatch = diff;
    return con_series;
}

int getdiff(void)
{

    time_t time1;
    struct tm stoptimetm;
    int hr, minutes;
    int diff = 0;

    time(&time1);                             // get current UNIX time
    struct tm *starttime = localtime(&time1); // convert UNIX to Year, Day, etc.
    stoptimetm = *starttime;                  // set stoptime to today

    printf("\nWrite the stoptime (E.g. 18:40): \n");
    scanf(" %d:%d", &hr, &minutes);

    stoptimetm.tm_hour = hr; // set given time into stoptime
    stoptimetm.tm_min = minutes;
    stoptimetm.tm_sec = 0; // reset seconds

    time_t stoptime = mktime(&stoptimetm); // convert back to UNIX

    if (difftime(stoptime, time1) <= 0)
    { // if stop time is next day, add 1 day in seconds
        diff = difftime(stoptime, time1) + 86400;
    }
    else
    {
        diff = difftime(stoptime, time1);
    }

    return diff;
}