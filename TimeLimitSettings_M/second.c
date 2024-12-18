#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void warnings(int choice, int time);

int main()
{
    int time = 10;
    int choice = 2;
    warnings(choice, time);
    return 0;
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