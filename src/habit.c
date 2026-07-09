#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "helpers.h"
#include "config.h"

typedef struct Habit {
    char h_name[STR_LENGTH]; // name of the habit
    char init_date[STR_LENGTH]; // date user started tracking the habit
    bool reset; // if user has reset streak, this is `true`
    char reset_date[STR_LENGTH]; // if reset == true, this is new reference date
    int h_best; // best streak user has had for this habit
} Habit;

// initialize new habit
Habit* init_habit(char name[]) {
    Habit* h = malloc(sizeof(Habit));

    if (h == NULL){
        return NULL;
    }

    // get date
    char today[STR_LENGTH];
    get_today(today, sizeof(today));

    // fills Habit members
    strcpy(h->h_name, name);
    strcpy(h->init_date, today);
    h->reset = false;
    h->h_best = 0;

    return h;
}

// save habit
int save_habit(Habit* h) {
    // create file path
    char path[STR_LENGTH];
    snprintf(path, sizeof(path), "data/%s.txt", h->h_name);
    printf("Full path: %s\n", path);

    // check if file already exists
    FILE *check = fopen(path, "r");
    if (check != NULL) {
        fclose(check);
        printf("File \"%s\" already exists.\n", path);

        return 1;
    }

    FILE *fptr = fopen(path, "w");
    if (fptr == NULL) { // file creation failed
        printf("File creation for \"%s\" failed\n", path);

        return 1;
        }  

    // add template data
    fprintf(fptr, "h_name:%s\n", h->h_name);
    fprintf(fptr, "reset:%d\n", h->reset);
    fprintf(fptr, "reset_date:\n");
    fprintf(fptr, "init_date:%s\n", h->init_date);
    fprintf(fptr, "best:%d\n", h->h_best);
    fclose(fptr);

    printf("Habit data created at \"%s\"\n", path);

    return 0;
};

int delete_habit(char* filename) {
    int i = 0; // for iterating over files

    // for reading dir
    struct dirent *de;

    // open directory
    DIR *dir = opendir(DATA_PATH);
    if (dir == NULL){
        printf("Failed to open directory.\n");
        return 1;
    } 

    // read files in directory
    while ((de = readdir(dir)) != NULL && i < 10) {
        if (strstr(de->d_name, filename) != NULL){ // file was found
            // create file path
            char file[STR_LENGTH];
            snprintf(file, sizeof(file), "data/%s", de->d_name);
            // delete file
            if (remove(file) == 0) {
                printf("File successfully erased!\n");
            } else {
                printf("Error deleting file.\n");
            }

            break;
        } else {continue;}
    }

    return 0;
}

int get_current(char path[]) {
    struct tm* time0 = get_ref_date(path); // get reference date from file
    time_t t0 = mktime(time0); // convert into seconds since Epoch 
    time_t t1 = time(NULL); // time now (equals today's date)

    // date diff
    double diff = difftime(t1, t0);
    int days = (int)(diff / 86400);

    return days;
}

struct tm* get_ref_date(char path[]) {
    char buffer[100];
    struct tm *date = malloc(sizeof(struct tm));

    FILE *fptr = fopen(path, "r");
    if (fptr == NULL){
        printf("File couldn't be opened.");

        return 1;
    }
 
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if (strstr(buffer, "reset:1") != NULL) { // has been reset before
                if (fgets(buffer, sizeof(buffer), fptr) == NULL){ // capture next line
                    printf("failure to cap line after reset");
                };
                if (strstr(buffer, "reset_date") != NULL) {
                    int year, month, day;

                    sscanf(buffer, "reset_date:%d/%d/%d", &year, &month, &day);
                    date->tm_year = year - 1900;
                    date->tm_mon = month;
                    date->tm_mday = day;
                    
                    break;
                } 
            }
        if (strstr(buffer, "init_date:") != NULL) { // init date found
            int year, month, day;

            sscanf(buffer, "init_date:%d/%d/%d", &year, &month, &day);
            date->tm_year = year - 1900;
            date->tm_mon = month;
            date->tm_mday = day;

            break;
        }
    }
    
    fclose(fptr);
    return date;
}
