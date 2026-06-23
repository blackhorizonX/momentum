#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

char **find_files(char *path);

int main(){
    
    char **files = find_files("data/");
    int i = 0;
    while (i < 10) {
        printf("File: %s\n", files[i]);
        i++;
    }

    return 0;
}

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
            char *file = malloc(sizeof(de->d_name));
            strcpy(file, de->d_name);
            files[i] = file; // add to array
            i++; // inc for next position

            printf("Matching file name: %s\n", de->d_name);
            free(file);
        }
    }

    return files;
}
