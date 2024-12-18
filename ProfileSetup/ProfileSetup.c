#include "ProfileSetup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

//Prototypes
void createProfile();
void viewProfile();
void listProfiles();
int profileExists(const char* profileName);
void addProfileToFile(const char* profileName);

int almostmain() {
    int choice;

    do {
        printf("\nWelcome to TouchGrass\n");
        printf("1. Create Profile\n");
        printf("2. Choose Profile\n");
        printf("3. List All Profiles\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createProfile();
                break;
            case 2:
                viewProfile();
                break;
            case 3:
                listProfiles();
                break;
            case 4:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

//Create new profile
void createProfile() {
    char profileName[MAX_LENGTH];
    char settings[MAX_LENGTH];
    char filename[MAX_LENGTH];
    FILE *file;

    printf("Enter your profile name: ");
    scanf("%s", profileName);

    //Check if the profile already exists
    if (profileExists(profileName)) {
        printf("Profile '%s' already exists.\n", profileName);
        return;
    }

    //Create a new file for the profile settings
    snprintf(filename, MAX_LENGTH, "%s.txt", profileName);
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating profile file");
        return;
    }

    //Input initial settings
    printf("Enter initial settings for the profile: ");
    getchar(); //Clears the leftover '\n', but can also use %[^\n]
    fgets(settings, MAX_LENGTH, stdin);
    fprintf(file, "%s", settings);
    fclose(file);

    //Add the profile name to the profiles list
    addProfileToFile(profileName);

    printf("Profile '%s' created successfully!\n", profileName);
}

//View and edit a profile
void viewProfile() {
    char profileName[MAX_LENGTH];
    char filename[MAX_LENGTH];
    char line[MAX_LENGTH];
    FILE *file;

    printf("Enter the profile name to view: ");
    scanf("%s", profileName);

    //Check if the profile exists
    if (!profileExists(profileName)) {
        printf("Profile '%s' does not exist.\n", profileName);
        return;
    }
    
    //Checks if file exists
    snprintf(filename, MAX_LENGTH, "%s.txt", profileName);
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening profile file");
        return;
    }

    printf("\nProfile Settings for '%s':\n", profileName);
    while (fgets(line, MAX_LENGTH, file) != NULL) {
        printf("%s", line);
    }
    fclose(file);

    //Ask if the user wants to edit the settings
    int choice;
    printf("\nDo you want to edit the settings? (1 for Yes, 0 for No): ");
    scanf("%d", &choice);

    if (choice == 1) {
        file = fopen(filename, "a"); 
        if (file == NULL) {
            perror("Error opening file to edit settings");
            return;
        }

        printf("Enter new settings to add:\n");
        getchar(); //Clears the leftover '\n'
        fgets(line, MAX_LENGTH, stdin);
        fprintf(file, "%s", line);
        fclose(file);

        printf("Settings updated successfully!\n");
    }
}

//List all profiles
void listProfiles() {
    FILE *file = fopen("profiles.txt", "r");
    char profileName[MAX_LENGTH];

    if (file == NULL) {
        printf("No profiles found.\n");
        return;
    }

    printf("\nExisting Profiles:\n");
    while (fgets(profileName, MAX_LENGTH, file) != NULL) {
        profileName[strcspn(profileName, "\n")] = '\0'; //removes the newline
        printf("- %s\n", profileName);
    }

    fclose(file);
}

//Check if a profile exists
int profileExists(const char* profileName) {
    FILE *file = fopen("profiles.txt", "r");
    char existingProfile[MAX_LENGTH];

    if (file == NULL) {
        return 0; //No profiles exist
    }

    while (fgets(existingProfile, MAX_LENGTH, file) != NULL) {
        existingProfile[strcspn(existingProfile, "\n")] = '\0';
        if (strcmp(existingProfile, profileName) == 0) {
            fclose(file);
            return 1; //Profile exists
        }
    }

    fclose(file);
    return 0;
}

//Add profile name to "profiles.txt"
void addProfileToFile(const char* profileName) {
    FILE *file = fopen("profiles.txt", "a"); 
    if (file == NULL) {
        perror("Error opening profiles file");
        return;
    }

    fprintf(file, "%s\n", profileName);
    fclose(file);
}
