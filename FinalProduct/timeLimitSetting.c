#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
https://stackoverflow.com/questions/2594447/opening-a-specific-file-with-a-batch-file 

https://stackoverflow.com/questions/58467675/how-to-open-web-urls-using-c-language 

https://www.hexnode.com/mobile-device-management/help/script-to-force-close-apps-on-windows/#:~:text=Batch%20script,-Batch%20script%20to&text=The%20taskkill%20command%20terminates%20all,the%20app%20is%20case%20sensitive. */

void setTimeSetting(int *timeSettingChosen)
{
   #ifdef _WIN32
    const char *filename = "Warning.vbs";

    // Try to open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file)
    {
        // If the file exists, close it and do nothing
        fclose(file);
    }
    else
    {
        // If the file does not exist, make it
        file = fopen(filename, "w");
        if (!file)
        {
            perror("Error creating file");
            return;
        }
        fprintf(file, "x=msgbox(\"You have reached your watch-limit\",0, \"REMINDER!\")"); // the command going in the file
        fclose(file);
    }
    #elif __APPLE__
       FILE *File = fopen("warning.txt", "w");
        if (File == NULL)
        {
            perror("Fejl ved åbning af output-fil");
            return;
        }
         fprintf(File, "Your time is up!!!!");
         
    #endif

    printf("You can choose 3 different types of interventions for your binge-session.\n"
           "Choose what will happen when you have reached your watching limit:\n\n"
           "Press 1 to get a pop-up message.\n"
           "Press 2 to close your streaming service window.\n"
           "Press 3 to shut down your computer 5 minutes after your time is up.\n");
    while (*timeSettingChosen != 1 && *timeSettingChosen != 2 && *timeSettingChosen != 3)
    {
        scanf(" %d", timeSettingChosen);
    }
}

void startWarning(int choice, char nc, int newMovieTime, int conWatchTime)
{
    int timeToWait;
    if (nc == 'n')
    {
        timeToWait = newMovieTime;
    }
    else if (nc == 'c')
    {
        timeToWait = conWatchTime;
    }
    else
    {
        printf("Error with time setting.\n");
        return;
    }

    sleep(timeToWait);
    switch (choice)
    {
    case 1:
#ifdef _WIN32
        
        system("Warning.vbs");
#elif __APPLE__
        system("open warning.txt");
#endif
        break;
    case 2:
        printf("\nClosing streaming service...\n");
#ifdef _WIN32
        system("Warning.vbs");
        system("C:\\WINDOWS\\System32\\taskkill /F /T /IM chrome.exe > nul 2>&1");
        system("C:\\WINDOWS\\System32\\taskkill /F /T /IM msedge.exe > nul 2>&1");
#elif __APPLE__
        system("open warning.txt");
        system("pkill Safari");
#endif

        break;
    case 3:
        printf("\nTurning off your computer in 5 minutes\n");
        system("C:\\WINDOWS\\System32\\shutdown /s /t 300");
        break;

    default:
        break;
    }
}
