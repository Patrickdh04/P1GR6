#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void warnings(int choice, int time);

int choice();

int main()
{
    int result = choice();

    int time = 10;
    int choice = 2;
    warnings(choice, time);

    return EXIT_SUCCESS;
}

int choice()
{
    int choice;
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
            return EXIT_FAILURE;
        }
        fprintf(file, "x=msgbox(\"You have reached your watch-limit\",0, \"REMINDER!\")"); // the command going in the file
        fclose(file);
    }

    printf("You can choose 3 different types of interventions for your binge-session.\n"
           "Choose what will happen when you have reached your watching limit:\n\n"
           "Press 1 to get a pop-up message.\n"
           "Press 2 to close your streaming service window.\n"
           "Press 3 to shut down your computer 5 minutes after your time is up.\n");

    while (choice < 1 || choice > 3)
    {
        scanf("%d", &choice);
    }

    return choice;
}

void warnings(int choice, int time)
{
   // sleep(time);
    switch (choice)
    {
    case 1:
        system("Warning.vbs");
        break;
    case 2:
        system("Warning.vbs");
        printf("\ntrying to close Netflix and chrome\n");
        system("C:\\WINDOWS\\System32\\taskkill /IM chrome.exe");
        system("C:\\WINDOWS\\System32\\taskkill /IM netflix.exe");
        break;
    case 3:
        printf("\nClosing the computer in 5 minutes\n");
        system("C:\\WINDOWS\\System32\\shutdown /s /t 300");
        break;

    default:
        break;
    }
}
