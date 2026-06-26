#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

// searches the directory given by `char *path` and returns an array of files for up to 10 .csv files in the directory.
char **find_files(char *path) {
    char **files = malloc(10 * sizeof(char *)); // room for 10 files
    int i = 0; // for iterating over files

    // compile regex for '.csv'
    regex_t regx;
    int result = regcomp(&regx, ".*\\.csv$", REG_EXTENDED);
    if (result == 0) {
        printf("Regex expression compiled successfully.\n");
    } else {
        printf("Failed to compile regex expression.\n");
    }

    // for reading dir
    struct dirent *de;

    // open directory
    DIR *dir = opendir(path);
    if (dir == NULL){
        printf("Failed to open directory.\n");
    } else {
        printf("Directory successfully accessed.\n");
    }

    // read files in directory
    while ((de = readdir(dir)) != NULL) {
        result = regexec(&regx, de->d_name, 0, NULL, 0); // perform regex comparison here

        // check for match
        if (result != 0){ // no match

            continue;
        } else if (result == 0) { // match
            char *file = malloc(strlen(de->d_name) + 1);
            strcpy(file, de->d_name);
            files[i] = file; // add to array
            i++; // inc for next position

            printf("Matching file name: %s\n", de->d_name);
        }
    }

    return files;
}

// returns the best streak from a file
int get_best(char *file){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("File failed to open\n");
        return 1;
    }

    int c; // read input
    bool swtch = false;
    int best = 0; 
    int num = 0; // to build multi-digit numbers

    // main loop
    while ((c = fgetc(fptr)) != EOF) {
        // if true, number of interest is in buffer
        if (swtch) { 
            if (c == '\n'){ // capture number, flush
                best = (num > best) ? num : best; // check if num is bigger
                num = 0;
                swtch = false;
                continue;
            } else if (c >= '0' && c <= '9') { // protect against reading header
                num = (num * 10) + c - '0';
                continue;
            }
        } 

        // numbers of interest will be next in buffer
        if (c == ',') {
            swtch = true;
            continue;
        }
    }

    fclose(fptr);
    return best;
}

int get_current(char *file){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("File failed to open\n");
        return 1;
    }

    int c; // read input
    bool swtch = false;
    int curr; 
    int num = 0; // to build multi-digit numbers

    // main loop
    while ((c = fgetc(fptr)) != EOF) {
        // if true, number of interest is in buffer
        if (swtch) { 
            if (c == '\n'){ // capture number, flush
                curr = num; // assign current
                num = 0; // flush number
                swtch = false;
                continue;
            } else if (c >= '0' && c <= '9') { // protect against reading header
                num = (num * 10) + c - '0';
                continue;
            }
        } 

        // numbers of interest will be next in buffer
        if (c == ',') {
            swtch = true;
            continue;
        }
    }

    fclose(fptr);
    return curr;
}

// increment streak value in given file
// format: 2026/06/26,1
int increment(char *path) {
    int curr;
    curr = get_current(path); // get current streak

    FILE *fptr = fopen(path, "a"); // open file
    if (fptr == NULL) {
        printf("File failed to open\n");
        return 1;
    }

    // get date string
    char date[14];
    // raw time
    time_t raw_time = time(NULL);
    struct tm *local = localtime(&raw_time);
    // save to date string
    snprintf(date, sizeof(date),
            "%04d/%02d/%02d",
            local->tm_year + 1900,
            local->tm_mon + 1,
            local->tm_mday);

    // append new data
    fprintf(fptr, "%s,%d\n", date, (curr + 1));
    fclose(fptr);

    return 0;
}
