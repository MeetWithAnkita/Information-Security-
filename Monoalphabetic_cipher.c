#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char key[], char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                ciphertext[i] = key[plaintext[i] - 'A']; // Map uppercase letters
            } else {
                ciphertext[i] = tolower(key[plaintext[i] - 'a']); // Map lowercase letters
            }
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
}

void decrypt(char ciphertext[], char key[], char plaintext[]) {
    char reverseKey[26];
    for (int i = 0; i < 26; i++) {
        reverseKey[key[i] - 'A'] = 'A' + i; // Create reverse mapping for decryption
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                plaintext[i] = reverseKey[ciphertext[i] - 'A']; // Map uppercase letters
            } else {
                plaintext[i] = tolower(reverseKey[toupper(ciphertext[i]) - 'A']); // Map lowercase letters
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
}

int main() {
    char plaintext[100], ciphertext[100], decryptedText[100];
    char key[27]; // 26 unique characters + null character
    
    printf("Enter plain text: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character from input

    printf("Enter 26-letter key (unique characters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character from input

    if (strlen(key) != 26) {
        printf("Error: Key must contain exactly 26 unique characters.\n");
        return 1;
    }

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
