#include <stdio.h>
#include <string.h>

// Function to reverse a string
void reverseString(char *str) {
    if (str == NULL || str[0] == '\0') {
        return;
    }

    // Calculate the length of the string
    int length = strlen(str);

    // Swap characters from the start and end
    for (int i = 0; i < length / 2; i++) {
        // Swap str[i] and str[length - 1 - i]
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character from fgets
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    // Reverse the string
    reverseString(str);

    printf("Reversed string: %s\n", str);

    return 0;
}
