#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *keyword, char *ciphertext) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(keyword);

    for (int i = 0, j = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char shift = tolower(keyword[j % keyLen]) - 'a';
            if (isupper(plaintext[i]))
                ciphertext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            else
                ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            j++;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    
    ciphertext[textLen] = '\0'; 
}

void decrypt(char *ciphertext, char *keyword, char *plaintext) {
    int textLen = strlen(ciphertext);
    int keyLen = strlen(keyword);

    for (int i = 0, j = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char shift = tolower(keyword[j % keyLen]) - 'a';
            if (isupper(ciphertext[i]))
                plaintext[i] = 'A' + (ciphertext[i] - 'A' - shift + 26) % 26;
            else
                plaintext[i] = 'a' + (ciphertext[i] - 'a' - shift + 26) % 26;
            j++;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[textLen] = '\0'; 
}

int main() {
    char plaintext[256], keyword[256], ciphertext[256], decryptedText[256];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; 

    encrypt(plaintext, keyword, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, keyword, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
