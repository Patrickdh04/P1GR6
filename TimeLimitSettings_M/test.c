#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void choice(int time);

int main(void)
{

    int time = 0;
    printf("Time is %d", time);
    choice(0);
    time = 10;
    printf("Time is %d", time);
    choice(time);
}

void choice(int time)
{
    static int choice;

    if (time == 0)
    {
        printf("\nYou now have 3 options:\n" 
        "(1) Get a messege when your time is up.\n"
        "(2) Close the program when your time is up.\n"
        "(3) Shutdown your comptuter 10 minutes after your time is up.\n");

        scanf("%d", &choice);
        return;
    }

    if (time >= 0)
    {
        while (choice == 1)
        {
            sleep(time);
            system("Warning.vbs");
            break;
        }

        while (choice == 2)
        {
            sleep(time);
            system("Warning.vbs");
            system("C:\\WINDOWS\\System32\\taskkill /IM chrome.exe");
            system("C:\\WINDOWS\\System32\\taskkill /IM netflix.exe");
            break;
        }

        while (choice == 3)
        {

            sleep(time);
            system("C:\\WINDOWS\\System32\\shutdown /s /t 600");
        }
    }
    return;
}