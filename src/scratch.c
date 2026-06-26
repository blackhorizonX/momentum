#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file.c"

int main() {
    int best;
    int curr;
    char path[] = "../data/gym.csv";

    best = get_best(path);
    printf("Best: %d\n", best);

    curr = get_current(path);
    printf("Current: %d\n", curr);

    if(increment(path) != 0){
        printf("increment failed.");
    }

    curr = get_current(path);
    printf("Current after increment: %d\n", curr);

    return 0;
}
