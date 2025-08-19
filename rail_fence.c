#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Remove spaces from string
void removeSpaces(char *src) {
    char *dst = src;
    while (*src) {
        if (!isspace((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

// Encrypt the plaintext using Rail Fence Cipher
void encryptRailFence(char *text, int key, char *result) {
    int len = strlen(text);
    char rail[key][len];

    // Initialize with '\n'
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    // Fill rail matrix in zigzag
    int row = 0, dir_down = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        rail[row][i] = text[i];
        row += dir_down ? 1 : -1;
    }

    // Read the matrix row by row
    int idx = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                result[idx++] = rail[i][j];

    result[idx] = '\0';
}

// Decrypt the ciphertext using Rail Fence Cipher
void decryptRailFence(char *cipher, int key, char *result) {
    int len = strlen(cipher);
    char rail[key][len];

    // Initialize rail with '\n'
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    // Mark the positions with '*'
    int row = 0, dir_down = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        rail[row][i] = '*';
        row += dir_down ? 1 : -1;
    }

    // Fill the rail matrix with ciphertext characters
    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*' && index < len)
                rail[i][j] = cipher[index++];

    // Read matrix in zigzag order to reconstruct original message
    row = 0, dir_down = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        result[i] = rail[row][i];
        row += dir_down ? 1 : -1;
    }

    result[len] = '\0';
}

int main() {
    char plaintext[100], noSpaceText[100], encrypted[100], decrypted[100];
    int key;

    printf("Enter plain text: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    strcpy(noSpaceText, plaintext);
    removeSpaces(noSpaceText);

    printf("Enter key (number of rails): ");
    scanf("%d", &key);

    encryptRailFence(noSpaceText, key, encrypted);
    decryptRailFence(encrypted, key, decrypted);

    printf("\nEncrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
