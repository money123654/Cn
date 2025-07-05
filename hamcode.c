#include <stdio.h>
#include <math.h>

// Function to calculate and insert parity bits in the Hamming code
void generateHammingCode(int dataBits[], int m, int hammingCode[], int r) {
    int i, j, k = 0;
    
    // Insert data bits into the correct positions
    for (i = 0,j=0; i < m + r; i++) {
        if ((i + 1) == pow(2, k)) {
            hammingCode[i] = 0;  // Placeholder for parity bit
            k++;
        } else {
			printf("%d  ",dataBits[j]);
            hammingCode[i] = dataBits[j++];
        }
    }

    // Calculate parity bits
    for (i = 0; i < r; i++) {
        int position = pow(2, i);
        int parity = 0;

        for (j = position - 1; j < m + r; j += 2 * position) {
            for (k = j; k < j + position && k < m + r; k++) {
                parity ^= hammingCode[k];  // XOR operation
            }
        }
        hammingCode[position - 1] = parity;  // Store parity bit
    }
}

// Function to detect and correct errors
void detectAndCorrectError(int hammingCode[], int m, int r) {
    int errorPosition = 0;

    // Compute syndrome (error detection)
    for (int i = 0; i < r; i++) {
        int position = pow(2, i);
        int parity = 0;

        for (int j = position - 1; j < m + r; j += 2 * position) {
            for (int k = j; k < j + position && k < m + r; k++) {
                parity ^= hammingCode[k];  // XOR for checking parity
            }
        }
        if (parity != 0) {
            errorPosition += position;
        }
    }

    // Correct error if found
    if (errorPosition != 0) {
        printf("Error detected at position: %d\n", errorPosition);
        hammingCode[errorPosition - 1] ^= 1;  // Flip the erroneous bit
        printf("Error corrected!\n");
    } else {
        printf("No error detected.\n");
    }
}

// Function to print Hamming Code
void printHammingCode(int hammingCode[], int size) {
    printf("Hamming Code: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", hammingCode[i]);
    }
    printf("\n");
}

int main() {
    int m;  // Number of data bits
    printf("Enter the number of data bits: ");
    scanf("%d", &m);

    int r = 0;  // Number of parity bits
    while (pow(2, r) < m + r + 1) {
        r++;
    }

    int dataBits[m];
    printf("Enter %d data bits (MSB to LSB): ", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &dataBits[i]);
    }

    int hammingCode[m + r];
    generateHammingCode(dataBits, m, hammingCode, r);

    printf("\nGenerated Hamming Code:\n");
    printHammingCode(hammingCode, m + r);

    // Simulate an error for testing (change one bit)
    int errorPos;
    printf("\nEnter error position (1 to %d) to introduce an error, or 0 for no error: ", m + r);
    scanf("%d", &errorPos);

    if (errorPos > 0 && errorPos <= m + r) {
        hammingCode[errorPos - 1] ^= 1;  // Flip bit
        printf("Error introduced at position %d!\n", errorPos);
    }

    printf("\nReceived Hamming Code:\n");
    printHammingCode(hammingCode, m + r);

    // Detect and correct error
    detectAndCorrectError(hammingCode, m, r);

    // Print corrected Hamming Code
    printf("\nCorrected Hamming Code:\n");
    printHammingCode(hammingCode, m + r);

    return 0;
}
