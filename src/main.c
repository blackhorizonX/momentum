#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "habit.c"
#include "file.c"

int main() {
    bool flow = true;
    int input;

    // initial input block
    while (flow) {
        printf("Hello! Choose an option.\n"
        "1) Create new habit\n"
        "2) Delete habit\n"
        "3) View current habits\n"
        "4) Exit\n");
        
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
        case 1: {// create new Habit
            Habit *habit = malloc(sizeof(Habit));

            if (init_habit(habit) == 0){
                printf("Habit successfully created!\n");
                free(habit);

            } else {
                printf("Failure during habit creation.\n");
                free(habit);
            };

            break;
        }
        case 2: {// delete habit
            char input[100];
            printf("Type the name of the habit you want to delete: ");

            fgets(input, sizeof(input), stdin);
            // remove \n
            input[strcspn(input, "\n")] = '\0';

            // ensure it was a valid file
            char **arr;
            arr = find_files("../data/"); // get array of files
                
            // search for file match
            bool found = false;
            for (int i = 0; arr[i] != NULL; i++) {
                if (strstr(arr[i], input) != NULL) {
                    found = true;
                    break;
                }
            }

            // check if match was found
            if (found) {
                printf("File found.\n");
                char path[100];
                snprintf(path, sizeof(path), "../data/%s.csv", input);
                remove(path); // delete
            } else {
                printf("Couldn't verify file exists.");
                return 1;
            }

            free(arr);
            break;
        }
        case 3: {// view all
            char **arr;
            arr = find_files("../data/");

            // print file list
            for (int i = 0; arr[i] != NULL; i++) {
                printf("%d) %s\n", i+1, arr[i]);
            }

            free(arr);
            break;
        }
        case 4: { 
            printf("Exiting...");
            return 0; //exit
        default:
            printf("Unable to associate input with action.");
        }
    }

    return 0;
};
