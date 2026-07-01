#include <stdio.h>
#include <string.h>
#include <time.h>

// gets the date from system
char* get_today() {
    // get date string
    char today[MAX_LENGTH];
    // raw time
    time_t raw_time = time(NULL);
    struct tm *local = localtime(&raw_time);
    // save to date string
    snprintf(today, sizeof(today),
            "%04d/%02d/%02d",
            local->tm_year + 1900,
            local->tm_mon + 1,
            local->tm_mday);

    return today;
}

// flush things from stdin buffer after inputs
void flush() {
    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        // discard the rest of the line
    }
}
