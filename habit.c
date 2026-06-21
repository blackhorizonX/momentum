#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Habit data type
typedef struct Habit {
    int best;
    int current;

    char name[24];
} Habit;

// create a new Habit
int init_habit(Habit *h) {
    // initialize
    h->best = 0;
    h->current = 0;

    // fill name
    printf("Enter habit name (ten characters or less): ");
    scanf("%10s", h->name);

    //initialize file
    char file[24];
    strcpy(file, h->name);
    printf("name copy: %s\n", file);

    char ext[5] = ".csv\0";
    strcat(file, ext);
    printf("file name: %s\n", file);

    char path[11] = "data/\0";
    strcat(path, file);
    printf("Full path: %s\n", path);

    // create file
    if (fopen(path, "r") != NULL) { // file already exists
        printf("File \"%s\" already exists.\n", path);
        return 1;
    } else if (fopen(path, "r") == NULL) {
        FILE *fptr = fopen(path, "w");

        if (fptr == NULL) { // file creation failed
            printf("File creation for \"%s\" failed\n", path);
            return 1;
        } else { // file creation success
        printf("file for habit \"%s\" created at \"%s\"\n", h->name, path);
        }
    }

    return 0;
};


// displayed at execution
void greeting() {
    printf("Hello! Choose an option.\n"
        "1) Create new habit\n"
        "2) Exit\n");
};

int get_input() {
    //receive
    int x;
    scanf("%d", &x);

    //validate
    if (x < 0 || x > 10) { 
        return -1; //invalid input
    }
    else {
        return x;
    }
};
