#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutils.h"

int main() {
    int choice;
    char input[256];

    printf("Choose an option:\n");
    printf("1. Reverse string\n");
    printf("2. Trim string\n");
    printf("3. Convert string to int\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);
    getchar(); // consume newline left by scanf

    printf("Enter your string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // remove trailing newline

    if (choice == 1) {
        str_reverse(input);
        printf("Reversed: '%s'\n", input);
    } else if (choice == 2) {
        str_trim(input);
        printf("Trimmed: '%s'\n", input);
    } else if (choice == 3) {
        int value;
        if (str_to_int(input, &value)) {
            printf("Converted number: %d\n", value);
        } else {
            printf("Invalid number: %s\n", input);
        }
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}