#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>

#define AMOUNTOFGENRES 21

typedef struct pref pref;
typedef struct conpref conpref;

// Prototypes
pref new_rec(void);
conpref con_rec(void);
int getdiff(void);

int main(void)
{
    char nc;
    do
    { // New recommendation or continue with series?
        printf("Do you want a new recommendation or continue watching a series? (n for new / c for continue): \n");
        Sleep(100);
        nc = getchar();
        while (getchar() != '\n'); 
    } while (nc != 'n' && nc != 'c'); // check if user typed n or c, repeat if not

    if (nc == 'n')
    {
        pref preference = new_rec(); // run new recommendation data collection
    }
    else if (nc == 'c')
    {
        conpref series = con_rec(); // run continue series data collection
    }
    else
    { // if somehow nc is not n or c
        printf("Problem with program, stopping...");
        exit(EXIT_FAILURE);
    }

    return 0;
}

pref new_rec(void)
{

    int g1 = -1, g2 = -1, g3 = -1;                    // g1-2-3 default index -1
    char gp1[10] = "?", gp2[10] = "?", gp3[10] = "?"; // 3 genre preferences
    char actor1[50] = "?", actor2[50] = "?", actor3[50] = "?";
    char genre[AMOUNTOFGENRES][12] = {"Action", "Adventure", "Animation", "Biography", "Comedy", "Crime", "Documentary", "Drama", "Family",
                          "Fantasy", "History", "Horror", "Musical", "Mystery", "Reality-TV", "Romance", "Sci-Fi", "Short", "Sport", "Thriller", "War"};

    char ar;

    int min_rating = 0, max_rating = 0;

    printf("\nWelcome to the Software 1 Group 6 Movie recommender!\n\n");

    do
    { // Get 3 genres
        printf("\nWrite 1 to 3 genres you want to see, separated by a comma (,) (Write '?' for a list of genres): \n");
        Sleep(100);
        scanf(" %9s, %9s, %9s", &gp1, &gp2, &gp3);

        for (int i = 0; i < AMOUNTOFGENRES; i++)
        {
            if (strcmp(gp1, genre[i]) == 0)
            {
                g1 = i;
            }
            else if (strcmp(gp2, genre[i]) == 0)
            {
                g2 = i;
            }
            else if (strcmp(gp3, genre[i]) == 0)
            {
                g3 = i;
            } // Get the 21 genre indexes 0-20
        }

        if (strcmp(gp1, "?") == 0)
        { // print list of genres
            printf("\nAction, Adventure, Animation, Biography, Comedy, Crime, Drama, Family, \nFantasy, History, Horror, Musical, Mystery, Reality-TV, Romance, Sci-Fi, Short, Sport, Thriller, Documentary, War");
        }

    } while (g1 == -1); // repeat if no valid genre 1


    printf("\nWrite 0 to 3 actors you want to see, separated by a comma (,) (Press enter to skip): \n");
    Sleep(100);
    scanf(" %49s, %49s, %49s", &actor1, &actor2, &actor3);

    do
    {
        printf("\nDo you want to be recommended 18+ films? (y/n): \n");
        scanf(" %c", &ar);
    } while (ar != 'y' && ar != 'n'); // repeat if no valid answer

    do
    {
        printf("\nWrite the minimum IMDb rating you want to look for (whole number between 1 and 9): \n");
        Sleep(100);
        scanf(" %d", &min_rating);
    } while (min_rating < 0 || min_rating > 10); // repeat if not between 1 and 9

    do
    {
        printf("\nWrite the maximum IMDb rating you want to look for (whole number between 1 and 10): \n");
        Sleep(100);
        scanf(" %d", &max_rating);
    } while (max_rating <= min_rating || max_rating > 10); // repeat if not bigger than min_rating and less than 10

    int diff = getdiff(); // get time diff in seconds

    pref preference;
    // create struct of data
    strcpy(preference.genre1, genre[g1]);
    preference.genrepref1 = g1;
    strcpy(preference.genre2, genre[g2]);
    preference.genrepref2 = g2;
    strcpy(preference.genre3, genre[g3]);
    preference.genrepref3 = g3;

    strcpy(preference.actor1, actor1);
    strcpy(preference.actor2, actor2);
    strcpy(preference.actor3, actor3);

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
        scanf(" %49s", &seriesName);

    } while (seriesName == "?");

    int diff = getdiff(); // Get time diff in seconds

    conpref con_series;
    // create struct of data
    strcpy(con_series.seriesName, seriesName);
    con_series.timetowatch = diff;
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