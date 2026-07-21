#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reverses a given string.
 *
 * @param str  The input string to be reversed.
 * @param length  The length of the input string.
 *
 * @return  A pointer to the reversed string.
 */
char* reverse_string(char* str, int length) {
    // Create a new string to store the reversed string
    char* reversed_str = (char*)malloc((length + 1) * sizeof(char));
    
    if (reversed_str == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Reverse the string
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }

    // Copy the reversed string to the new string
    for (int i = 0; i < length; i++) {
        reversed_str[i] = str[i];
    }

    // Null-terminate the new string
    reversed_str[length] = '\0';

    return reversed_str;
}

int main() {
    char str[] = "Hello, World!";
    int length = strlen(str);
    char* reversed_str = reverse_string(str, length);

    if (reversed_str != NULL) {
        printf("Reversed string: %s\n", reversed_str);
        free(reversed_str);
    }

    return 0;
}
