#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int choice();

int main(){
    int result = choice();

    return EXIT_SUCCESS;
}

int choice()
{
    int choice;
    const char *filename = "Warning.vbs";

    // Try to open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file) {
        // If the file exists, close it and do nothing
        fclose(file);
    } else {
        // If the file does not exist, make it
        file = fopen(filename, "w");
        if (!file) {
            perror("Error creating file");
            return EXIT_FAILURE;
        }
        fprintf(file, "x=msgbox(\"Warning, you are over your time\", 0, \"Attention\")"); //the command going in the file
        fclose(file);
    }


        printf("\n you now have 3 options\n 1 to get a messege when your time is up\n 2 close the program when your time is up\n 3 shutdown your comptuter 10 minutes after your time is up\n");

        scanf("%d", &choice);

        while(choice < 1 || choice > 3)
        {
            printf("\n choose a number between 1 to 3\n");
            
            scanf("%d", &choice);
        }
        
        return choice;
    }
