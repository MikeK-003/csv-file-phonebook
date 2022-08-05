#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARRAY_SIZE 32
#define LARGE_SIZE 500

/*
    this program is a database that works with .csv files
    users have the options of creating a new entry on an existing or new file
    as well as deleting, editing, and looking up an entry on existing files
*/

// listing all functions down here
void printStartMenu();
void addEntry();
void createNewFile();
void importFile();
void deleteEntry();
void editEntry();
void lookUpEntry();
void printFile();
void getInput();

// what an entry will look like
struct entry {
    char name[ARRAY_SIZE];
    char town[ARRAY_SIZE];
    char state[ARRAY_SIZE];
    char last4digsphonenum[ARRAY_SIZE];
};

// print start menu
int main() {
    printStartMenu();
    return 0;
}

// choices presented
void printStartMenu() {
    char nameofinput[ARRAY_SIZE];
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

    getInput(&nameofinput);
    sscanf(nameofinput, "%d", &choice);

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
    char nameofinput[ARRAY_SIZE];
    char yesorno;
    struct entry new_entry;

    while (1) {
        printf("\nwould you like to add this entry to an existing file? Y/N: ");

        getInput(&nameofinput);
        sscanf(nameofinput, "%c", &yesorno);

        switch (yesorno) {
            case 'n':
            case 'N':
                // if user does not want to add entry to existing file, call new file create func and terminate this one
                printf("entered no, creating new .csv file...\n");
                createNewFile();
                exit(0);
            case 'y':
            case 'Y':
                // if user does want to add entry to existing file, call file import func and terminate this one
                printf("entered yes, accessing current .csv files...\n");
                importFile();
                exit(0);
            default:
                printf("invalid key\n");
                continue;
        }
    }
}

void createNewFile() {
    char nameofinput[ARRAY_SIZE];
    struct entry new_entry;
    FILE *input_file;

    while(1) {
        printf("\nenter the name of the .csv file you wish to create\nexample: asdf.csv = asdf.csv or asdf: ");
        getInput(&nameofinput);

        // if the last 4 chars of file name input = ".csv", do nothing. otherwise append ".csv" to file name input
        if (strcmp(&nameofinput[strlen(nameofinput)-4], ".csv") == 0) {
            // do nothing
        } else {
            strcat(nameofinput, ".csv");
        }

        // check if file currently exists
        if (input_file = fopen(nameofinput, "r")) {
            printf("this file currently exists, try again\n\n");
            fclose(input_file);
            continue;
        } else {
            printf("no file conflict detected\n\n");
            input_file = fopen(nameofinput, "a");
            break;
        }
    }

    if (input_file == NULL) {
        fprintf(stderr, "can't create the file!\n");
        exit (8);
    }

    printf("new file created\n\n");

    printf("enter a person's first and last name: ");
    getInput(&nameofinput);
    strcpy(new_entry.name, nameofinput);

    printf("enter the person's town: ");
    getInput(&nameofinput);
    strcpy(new_entry.town, nameofinput);

    printf("enter the person's state: ");
    getInput(&nameofinput);
    strcpy(new_entry.state, nameofinput);

    printf("enter last four digits of the person's phone number: ");
    getInput(&nameofinput);
    strcpy(new_entry.last4digsphonenum, nameofinput);

    fprintf(input_file, "full name,town,state,last4digsofphonenum\n");
    fprintf(input_file, "%s,%s,%s,%s\n", new_entry.name, new_entry.town, new_entry.state, new_entry.last4digsphonenum);

    printf("\na new entry has been added to the specified file\n");
    fclose(input_file);
}

void importFile() {
    char nameofinput[ARRAY_SIZE];
    struct entry new_entry;
    FILE *input_file;


    while (1) {
        printf("\nenter the name of the .csv file you wish to edit\nexample: asdf.csv = asdf.csv or asdf: ");
        getInput(&nameofinput);

        // if the last 4 chars of file name input = ".csv", do nothing. otherwise append ".csv" to file name input
        if (strcmp(&nameofinput[strlen(nameofinput)-4], ".csv") == 0) {
            // do nothing
        } else {
            strcat(nameofinput, ".csv");
        }

        // check if file currently exists
        if (input_file = fopen(nameofinput, "r")) {
            fclose(input_file);
            input_file = fopen(nameofinput, "a");
            break;
        } else {
            printf("this file is not in the directory, try again\n\n");
            continue;
        }
    }

    if (input_file == NULL) {
        fprintf(stderr, "can't find the file!\n");
        exit (8);
    }

    printf("chosen file opened\n\n");

    printf("enter a person's first and last name: ");
    getInput(&nameofinput);
    strcpy(new_entry.name, nameofinput);

    printf("enter the person's town: ");
    getInput(&nameofinput);
    strcpy(new_entry.town, nameofinput);

    printf("enter the person's state: ");
    getInput(&nameofinput);
    strcpy(new_entry.state, nameofinput);

    printf("enter last four digits of the person's phone number: ");
    getInput(&nameofinput);
    strcpy(new_entry.last4digsphonenum, nameofinput);

    fprintf(input_file, "%s,%s,%s,%s\n", new_entry.name, new_entry.town, new_entry.state, new_entry.last4digsphonenum);

    printf("\na new entry has been added to the specified file\n");
    fclose(input_file);
}

void deleteEntry() {
    char *comparison;
    char copyoffile[LARGE_SIZE];
    char copyofline[ARRAY_SIZE][ARRAY_SIZE];
    char nameofinput[ARRAY_SIZE];
    FILE *input_file;
    int ch;
    int columncounter = 0;
    int index = 0;
    int rowcounter = 0;

    while (1) {
        printf("\nenter the name of the .csv file you wish to edit\nexample: asdf.csv = asdf.csv or asdf: ");
        getInput(&nameofinput);

        // if the last 4 chars of file name input = ".csv", do nothing. otherwise append ".csv" to file name input
        if (strcmp(&nameofinput[strlen(nameofinput)-4], ".csv") == 0) {
            // do nothing
        } else {
            strcat(nameofinput, ".csv");
        }

        // check if file currently exists
        if (input_file = fopen(nameofinput, "r")) {
            fclose(input_file);
            input_file = fopen(nameofinput, "r+");
            break;
        } else {
            printf("this file is not in the directory, try again\n\n");
            continue;
        }
    }

    if (input_file == NULL) {
        fprintf(stderr, "can't find the file!\n");
        exit (8);
    }

    printf("chosen file opened\n\n");

    printf("enter the full name associated with the entry you want to delete: ");
    getInput(&nameofinput);

    // the idea behind the while loop below is as follows:
    // go through the entire file. have a 2d array to save each line of the file.
    // ideally, copyofline[0] is the entire first line of file, copyofline[1] is the second, and so on
    // then, rewind to the start of the file and begin printing out each copyofline[i] to a new file
    // if the line containing the name of the entry we want to delete is reached, do i++ to skip that line.
    // save the new file under the name of the old one and presto, file without said entry
    // the only problem is i can't do the first step in this.

    // copies entire file and keeps track of lines
    while (1) {
        ch = fgetc(input_file);
        copyoffile[index] = (char)ch;
        
        // while the current char isn't a newline...
        while (ch != '\n') {
            // ...have the 2d array fill up the columns (horizontal)
            copyofline[columncounter][rowcounter] = (char)ch;
            columncounter++;

            // when a newline is reached...
            if (ch == '\n') {
                // ...reset the columncounter (horizontal) and increment the rowcounter (vertical) by 1.
                // continue from top of while loop
                columncounter = 0;
                rowcounter++;
                continue;
            } else if (ch == EOF) {
                copyoffile[strlen(copyoffile)-1] = '\0';
                break;
                // i merged the break in this second while loop since the logic above can't normally exit on its own
            }
        }
    }

    // this entire thing results in a core dump

    printf("test: file is:\n%s\n", copyoffile);
    printf("test: line 1 is:\n%s\n", copyofline[0]);
    printf("test: line 2 is:\n%s\n", copyofline[1]);

    fclose(input_file);
}

void editEntry() {

}

void lookUpEntry() {

}

void printFile() {

}

void getInput(char *nameofinput) {
    fgets(nameofinput, ARRAY_SIZE, stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    fflush(stdin);
}