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
    while (choice == 1)
    {
        sleep(time);
        system("warning.vbs");
        break;
    }

    while (choice == 2)
    {
        sleep(time);
        system("warning.vbs");
        system("C:\\WINDOWS\\System32\\taskkill /IM chrome.exe");
        system("C:\\WINDOWS\\System32\\taskkill /IM netflix.exe");
        system("C:\\WINDOWS\\System32\\taskkill /pid 18356");
        break;
    }

    while (choice == 3)
    {

        sleep(time);
        system("C:\\WINDOWS\\System32\\shutdown /s /t 600");
        break;
    }
}