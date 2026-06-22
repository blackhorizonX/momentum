#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    char date[14];

    // raw time
    time_t raw_time = time(NULL);

    struct tm *local = localtime(&raw_time);

    printf("Date: %04d/%02d/%02d\n",
            local->tm_year + 1900,
            local->tm_mon + 1,
            local->tm_mday);
    
    // save to date string
    snprintf(date, sizeof(date),
            "%04d/%02d/%02d\n",
            local->tm_year + 1900,
            local->tm_mon + 1,
            local->tm_mday);

    printf("%s", date);

    return 0;
}
