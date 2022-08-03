#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// listing all functions down here
void printStartMenu();
void addEntry();
void importFile();
void saveToFile();
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
    char nameofarray[32];
    int value;

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

    fgets(nameofarray, sizeof(nameofarray), stdin);
    sscanf(nameofarray, "%d", &value);
    fflush(stdin);

    switch (value) {
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

// add entry, will also use importFile() and saveToFile()
void addEntry() {
    char nameofarray[32];
    char nameofchar;
    int value;

    printf("would you like to add this entry to an existing file? Y/N: ");

    fgets(nameofarray, sizeof(nameofarray), stdin);
    sscanf(nameofarray, "%c", &nameofchar);
    fflush(stdin);

    switch (nameofchar) {
        case 'n':
        case 'N':
            // if user does not want to add entry to existing file, break switch case and carry out rest of func
            // once entry is made, file export func will be called
            printf("entered no, creating new .csv file...\n\n");
            break;
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

    // there are multiple things wrong here:
    // 1. as the rest of this function gets executed, the fgets below will be ignored and the func call below will not
    // 2. after the bottom of this function is reached, everything below this point gets executed AGAIN for some reason.

    printf("this gets printed twice!\n");
    fgets(nameofarray, sizeof(nameofarray), stdin);
    sscanf(nameofarray, "%c", &nameofchar);
    fflush(stdin);
}

void importFile() {
    printf("here is a list of all the .csv files in the program's directory:\n\n");

}

void saveToFile() {
    printf("name your new file.\n");
    printf("naming your file after an existing one will not work.\n");
    printf("here is a list of all the .csv files in the program's directory:\n\n");

}

void deleteEntry() {
    char nameofarray[32];
    int value;

    printf("the below fgets will get entirely ignored: ");
    fgets(nameofarray, sizeof(nameofarray), stdin);
}

void editEntry() {

}

void lookUpEntry() {

}

void printFile() {

}