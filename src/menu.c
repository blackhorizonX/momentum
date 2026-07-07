#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "helpers.h"
#include "habit.h"
#include "config.h"

// get user's desired option
int get_option(int x) {
   int opt = fgetc(stdin);
   flush();

    if (opt < '1' || opt > '9') {
        return 1;
    }

    int option = opt - '0';
    x = option;
    printf("input: %d\n", x);

    return 0;
}



// display stats from active habits
int dashboard() {

    return 0;
}
