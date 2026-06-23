#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <regex.h>

int main() {
    // make an array of strings
    char *arr[5];


    char *s1 = "hello";
    char *s2 = "world";
    arr[0] = s1;
    arr[1] = s2;

    printf("first element in array: %s", arr[0]);
    printf("second element in array: %s", arr[1]);

    return 0;
}
