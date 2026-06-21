#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "habit.c"

int main() {
    bool flow = true;
    int input;
    Habit *habit = malloc(sizeof(Habit));

    // initial input block
    while (flow) {
        greeting();
        
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
            if (init_habit(habit) == 0){
                printf("Sucess\n");
            } else if (init_habit(habit) == 1){
                printf("Failure\n");
            };

        case 2:
            return 0; //exit
        default:
            printf("Unable to associate input with action.");
    }

    free(habit);
    return 0;
};
