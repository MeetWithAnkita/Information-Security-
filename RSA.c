#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function to calculate the greatest common divisor (GCD)
uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular multiplicative inverse
int64_t modInverse(int64_t a, int64_t m) {
    int64_t m0 = m;       // Save original value of m
    int64_t x0 = 0, x1 = 1; // These keep track of the result

    if (m == 1)
        return 0;         // If mod is 1, no inverse exists

    while (a > 1) {
        int64_t q = a / m;   // Divide a by m
        int64_t t = m;       // Save current m

        // Update m and a using remainder
        m = a % m;
        a = t;

        // Update x values
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make sure result is positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}


// Function to perform modular exponentiation (efficiently)
uint64_t power(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    base = base % mod; // Update base if it is more than mod
    while (exp > 0) {
        // If exp is odd, multiply base with result
        if (exp % 2 == 1)
            res = (res * base) % mod;
        // exp must be even now
        exp = exp >> 1; // exp = exp/2
        base = (base * base) % mod;
    }
    return res;
}

// Function to generate RSA keys
void generateKeys(uint64_t p, uint64_t q, uint64_t *n, uint64_t *e, uint64_t *d) {
    if (p == q) {
        printf("p and q cannot be equal.\n");
        exit(1);
    }
    *n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    *e = 5; // Choose a small e
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }
    *d = modInverse(*e, phi);
}

// Function to encrypt the message
uint64_t encrypt(uint64_t message, uint64_t n, uint64_t e) {
    return power(message, e, n);
}

// Function to decrypt the ciphertext
uint64_t decrypt(uint64_t ciphertext, uint64_t n, uint64_t d) {
    return power(ciphertext, d, n);
}

int main() {
    uint64_t p, q, n, e, d, message, ciphertext, decryptedMessage;

    printf("Enter two distinct prime numbers:\n");
    printf("p = ");
    scanf("%llu", &p);
    printf("q = ");
    scanf("%llu", &q);

    generateKeys(p, q, &n, &e, &d);

    printf("Public Key (n, e): (%llu, %llu)\n", n, e);
    printf("Private Key (n, d): (%llu, %llu)\n", n, d);

    printf("Enter message to encrypt (number): M = ");
    scanf("%llu", &message);

    ciphertext = encrypt(message, n, e);
    printf("Encrypted Message (Ciphertext) C = %llu\n", ciphertext);

    decryptedMessage = decrypt(ciphertext, n, d);
    printf("Decrypted Message M = %llu\n", decryptedMessage);

    return 0;
}