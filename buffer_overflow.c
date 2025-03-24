#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 8

int validatePassword(char *password) {
    int length = strlen(password);
    int hasDigit = 0;

    // Check length
    if (length < 8) {
        return 0;
    }

    // Check first character is uppercase
    if (!isupper(password[0])) {
        return 0;
    }

    // Check for at least one digit
    for (int i = 0; i < length; i++) {
        if (isdigit(password[i])) {
            hasDigit = 1;
            break;
        }
    }
    if (!hasDigit) {
        return 0;
    }

    // Check last character is uppercase
    if (!isupper(password[length - 1])) {
        return 0;
    }

    return 1;
}

int main() {
    char buffer[BUFFER_SIZE];
    char password[100];

    printf("Enter a password: ");
    scanf("%s", password);

    // Simulate buffer overflow
    strcpy(buffer, password);

    if (validatePassword(password)) {
        printf("Password is valid.\n");
    } else {
        printf("Password is invalid.\n");
    }

    // Display buffer content after overflow
    printf("Buffer content: %s\n", buffer);

    return 0;
}