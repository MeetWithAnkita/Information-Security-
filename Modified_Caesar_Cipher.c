// Write a C program to convert plaintext to ciphertext (encryption) and vice versa (decryption) using a modified Caesar cipher method.
// 	The key should be user-given as "4".
// 	Use "HELLO TIU" as the user input plaintext.

#include <stdio.h>
#include <string.h>

// Function to encrypt the plaintext
void encrypt(char plaintext[], char ciphertext[], int key) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];

        // Encrypt uppercase letters
        if (ch >= 'A' && ch <= 'Z') {
            ch = ((ch - 'A' + key) % 26) + 'A';
        }
        // Encrypt lowercase letters
        else if (ch >= 'a' && ch <= 'z') {
            ch = ((ch - 'a' + key) % 26) + 'a';
        }

        ciphertext[i] = ch;
    }
    ciphertext[i] = '\0';
}

// Function to decrypt the ciphertext
void decrypt(char ciphertext[], char decryptedtext[], int key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];

        // Decrypt uppercase letters
        if (ch >= 'A' && ch <= 'Z') {
            ch = ((ch - 'A' - key + 26) % 26) + 'A';
        }
        // Decrypt lowercase letters
        else if (ch >= 'a' && ch <= 'z') {
            ch = ((ch - 'a' - key + 26) % 26) + 'a';
        }

        decryptedtext[i] = ch;
    }
    decryptedtext[i] = '\0';
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char decryptedtext[100];
    int key;

    // Get the plaintext from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    // Remove newline character from plaintext
    plaintext[strcspn(plaintext, "\n")] = '\0';

    // Get the key from the user
    printf("Enter the key: ");
    scanf("%d", &key);
    // Clear the newline character left by scanf
    while (getchar() != '\n');

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, key);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedtext, key);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}