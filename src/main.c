#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "habit.c"

int main() {
    bool flow = true;
    int input;

    // initial input block
    while (flow) {
        printf("Hello! Choose an option.\n"
        "1) Create new habit\n"
        "2) Exit\n");
        
        input = get_input();
        if (input > 0){
            flow = false;
        }
        else {
            printf("Invalid input. Enter integer corresponding to an option.\n");
            continue;
        }
    }

    printf("testing input against cases...\n");
    // test valid input against cases
    switch (input) {
        case 1: // create new Habit
            Habit *habit = malloc(sizeof(Habit));

            if (init_habit(habit) == 0){
                printf("Habit successfully created!\n");
                free(habit);

            } else if (init_habit(habit) == 1){
                printf("Failure during habit creation.\n");
                free(habit);
            };
        case 2:
            return 0; //exit
        default:
            printf("Unable to associate input with action.");
    }

    return 0;
};
