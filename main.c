#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// habit data type
typedef struct habit {
    char *name;
    int best;
    int current;
} habit;

// declarations
habit *create_habit(char *name);
void greeting();
int get_input();

int main() {
    bool flow = true;
    int input;

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

    // test valid input against cases
    switch (input) {
        case 1: // create new habit
            printf("Name for new habit (ten characters or less): ");
            char name[11];
            scanf("%10s", name);
        case 2:
            return 0; //exit
        default:
            printf("Unable to associate input with action.");
    }

    return 0;
};

// create a new habit
habit *create_habit(char *name) {
    habit *h = malloc(sizeof(habit));
    h->name = name;
    h->best = 0;
    h->current = 0;

    return h;
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
