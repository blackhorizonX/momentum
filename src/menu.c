#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <assert.h>
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
    struct dirent *de; // for reading dir

    DIR *dir = opendir(DATA_PATH); // open directory
    if (dir == NULL){
        printf("Failed to open %s\n", DATA_PATH);
        return -1;
    } 
    
    while ((de = readdir(dir)) != NULL) { // read files in directory
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) { // skip over directory entries
            continue;
        }

        char file[STR_LENGTH]; // make full path
        snprintf(file, sizeof(file), "data/%s", de->d_name); 

        int best = get_best(file); // get best

        // get current
        struct tm *time0 = get_ref_date(file); // get reference date from habit within path
        int current = get_current(time0); // get current streak by subtracting ref date with current date
        free(time0);

        // Best should be updated if necessary

        printf("Habit: " ANSI_CYAN "%s" COLOR_RESET "\n", de->d_name); // print habit name

        if (current < best) {
            printf("Current Streak: " ANSI_RED "%d" COLOR_RESET "\n", current);
            printf("Best Streak: " ANSI_GREEN "%d" COLOR_RESET "\n", best);
        } else if (current >= best) {
            update_best(file, current); // update best in file
            best = get_best(file); // get best again from file
             
            assert(best == current); // ensure best is now equal to current

            printf("Current Streak: " ANSI_GREEN "%d" COLOR_RESET "\n", current);
            printf("Best Streak: " ANSI_GREEN "%d" COLOR_RESET "\n", best);
        }

        printf("\n"); // separate each habit by \n
    }

    closedir(dir);
    return 0;
}
