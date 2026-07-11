#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "helpers.h"
#include "habit.h"
#include "config.h"

// get user's desired option
int get_option(int* x) {
   int opt = fgetc(stdin);
   flush();

    if (opt < '1' || opt > '9') {
        return 1;
    }

    int option = opt - '0';
    *x = option;

    return 0;
}



// display stats from active habits
int dashboard() {
    // for reading dir
    struct dirent *de;

    // open directory
    DIR *dir = opendir(DATA_PATH);
    if (dir == NULL){
        printf("Failed to open %s\n", DATA_PATH);
        return -1;
    } 

    // read files in directory
    while ((de = readdir(dir)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }
        char file[STR_LENGTH];
        snprintf(file, sizeof(file), "data/%s", de->d_name); // make full path

        int best = get_best(file); // get best

        // get current
        struct tm *time0 = get_ref_date(file); // get reference date from habit within path
        int current = get_current(time0); // get current streak by subtracting ref date with current date
        free(time0);


        printf("Habit: " ANSI_CYAN "%s" COLOR_RESET "\n", de->d_name); // print habit name

        if (current < best) {
            printf("Current Streak: " ANSI_RED "%d" COLOR_RESET "\n", current);
        } else if (current >= best) {
            printf("Current Streak: " ANSI_GREEN "%d" COLOR_RESET "\n", current);
        }

        printf("Best Streak: " ANSI_GREEN "%d" COLOR_RESET "\n", best);

        printf("\n"); // separate each habit by \n
    }

    closedir(dir);
    return 0;
}
