#include <stdio.h>

void reverse_string(char* str) {
    int length = 0;
    char *start = str, *end = str;

    // Calculate the length of the string
    while (*end != '\0') {
        end++;
    }
    end--;  // Point to the last character

    while (start < end) {
        // Swap characters
        char temp = *start;
        *start = *end;
        *end = temp;

        // Move pointers towards the center
        start++;
        end--;
    }
}

int main() {
    char str[] = "Hello, world!";
    printf("Original string: %s\n", str);
    reverse_string(str);
    printf("Reversed string: %s\n", str);
    return 0;
}
