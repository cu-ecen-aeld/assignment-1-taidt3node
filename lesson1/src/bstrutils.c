#include "strutils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
// 1. Reverse a string in-place
void str_reverse(char *str) {
    if (!str) return;
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

// 2. Trim leading and trailing whitespace
void str_trim(char *str) {
    if (!str) return;
    char *start = str;
    while (isspace((unsigned char)*start)) start++; // skip leading spaces
    
    char *end = str + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--; // skip trailing spaces
    *(end + 1) = '\0';
    
    // shift trimmed string to the front
    memmove(str, start, end - start + 2);
}

// 3. Safely convert a string to an integer
int str_to_int(const char *str, int *out) {
    if (!str || !out) return 0;
    char *endptr;
    long val = strtol(str, &endptr, 10);

    if (*endptr != '\0') return 0; // invalid character found
    if (val > INT_MAX || val < INT_MIN) return 0; // overflow check

    *out = (int)val;
    return 1;
}