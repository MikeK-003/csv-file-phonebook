#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// listing all functions down here
void printStartMenu();
void addEntry();
void createNewFile();
void importFile();
void deleteEntry();
void editEntry();
void lookUpEntry();
void printFile();

// what an entry will look like
struct entry {
    char name[32];
    char town[32];
    char state[32];
    int last4digsphonenum;
};

// print start menu
int main() {
    printStartMenu();
    return 0;
}

// choices presented
void printStartMenu() {
    char nameofinput[32];
    int choice;

    printf("-------------------------------------------------\n");
    printf("\tphone book program - enter a key\n");
    printf("-------------------------------------------------\n\n");

    printf("press 1: add entry\n");
    printf("press 2: delete entry\n");
    printf("press 3: edit entry\n");
    printf("press 4: look up entry\n");
    printf("press 5: print .csv file\n");
    printf("press any other key: quit\n");
    printf("input choice: ");

    fgets(nameofinput, sizeof(nameofinput), stdin);
    sscanf(nameofinput, "%d", &choice);
    fflush(stdin);

    switch (choice) {
        case 1:
            addEntry();
            break;
        case 2:
            deleteEntry();
            break;
        case 3:
            editEntry();
            break;
        case 4:
            lookUpEntry();
            break;
        case 5:
            printFile();
            break;
        default:
            printf("quitting\n");
            exit(0);
    }
}

// add entry, will also use createNewFile() and importFile()
void addEntry() {
    char nameofinput[32];
    char nameofchar;
    int value;
    struct entry new_entry;

    printf("\nwould you like to add this entry to an existing file? Y/N: ");

    fgets(nameofinput, sizeof(nameofinput), stdin);
    sscanf(nameofinput, "%c", &nameofchar);
    fflush(stdin);

    switch (nameofchar) {
        case 'n':
        case 'N':
            // if user does not want to add entry to existing file, call new file create func and terminate this one
            printf("entered no, creating new .csv file...\n\n");
            createNewFile();
            exit(0);
        case 'y':
        case 'Y':
            // if user does want to add entry to existing file, call file import func and terminate this one
            printf("entered yes, accessing current .csv files...\n\n");
            importFile();
            exit(0);
        default:
            printf("invalid key, ");
            addEntry();
    }
}

void createNewFile() {
    char nameofinput[32];
    int value;
    struct entry new_entry;

    printf("enter the name of the .csv file you wish to create, do not include the file extension: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    fflush(stdin);

    strcat(nameofinput, ".csv");

    FILE *input_file;

    // check if file currently exists
    if (input_file = fopen(nameofinput, "r")) {
        printf("this file currently exists, try again\n");
        fclose(input_file);
        createNewFile();
    } else {
        printf("no file conflict detected\n");
        input_file = fopen(nameofinput, "a");
    }

    if (input_file == NULL) {
        fprintf(stderr, "can't create the file!\n");
        exit (8);
    }

    printf("new file created\n\n");

    printf("enter a person's first and last name: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    strcpy(new_entry.name, nameofinput);
    fflush(stdin);

    printf("enter the person's town: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    strcpy(new_entry.town, nameofinput);
    fflush(stdin);

    printf("enter the person's state: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    strcpy(new_entry.state, nameofinput);
    fflush(stdin);

    printf("enter last four digits of the person's phone number: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    sscanf(nameofinput, "%d", &value);
    new_entry.last4digsphonenum = value;

    fprintf(input_file, "full name,town,state,last4digsofphonenum\n");
    fprintf(input_file, "%s,%s,%s,%d\n", new_entry.name, new_entry.town, new_entry.state, new_entry.last4digsphonenum);

    printf("\na new entry has been added to the specified file\n");
    fclose(input_file);
}

void importFile() {
    char nameofinput[32];
    int value;
    struct entry new_entry;

    printf("enter the name of the .csv file you wish to edit, do not include the file extension: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    fflush(stdin);

    strcat(nameofinput, ".csv");

    FILE *input_file;
    input_file = fopen(nameofinput, "a");

    if (input_file == NULL) {
        fprintf(stderr, "can't find the file!\n");
        exit (8);
    }

    printf("chosen file opened\n\n");

    printf("enter a person's first and last name: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    strcpy(new_entry.name, nameofinput);
    fflush(stdin);

    printf("enter the person's town: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    strcpy(new_entry.town, nameofinput);
    fflush(stdin);

    printf("enter the person's state: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    strcpy(new_entry.state, nameofinput);
    fflush(stdin);

    printf("enter last four digits of the person's phone number: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
    sscanf(nameofinput, "%d", &value);
    new_entry.last4digsphonenum = value;

    fprintf(input_file, "%s,%s,%s,%d\n", new_entry.name, new_entry.town, new_entry.state, new_entry.last4digsphonenum);

    printf("\na new entry has been added to the specified file\n");
    fclose(input_file);
}

void deleteEntry() {
    char nameofinput[32];
    int value;

    printf("the below fgets will get entirely ignored: ");
    fgets(nameofinput, sizeof(nameofinput), stdin);
}

void editEntry() {

}

void lookUpEntry() {

}

void printFile() {

}