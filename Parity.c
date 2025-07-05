#include <stdio.h>

// Function to count the number of 1s in the binary representation of a number
int count_ones(int num) {
    int count = 0;
    while (num) {
		printf("%d  ",num);
        count += num & 1;  // Check the last bit
        num >>= 1;  // Right shift to check next bit
    }
    printf("\n\n");
    return count;
}

// Function to generate parity bit (0 for even parity, 1 for odd parity)
int generate_parity(int num, int parity_type) {
    int ones_count = count_ones(num);
    if (parity_type == 0) {  // Even parity
        return (ones_count % 2 == 0) ? 0 : 1;
    } else {  // Odd parity
        return (ones_count % 2 == 0) ? 1 : 0;
    }
}

// Function to check parity
int check_parity(int num, int parity_bit, int parity_type) {
    int ones_count = count_ones(num) + parity_bit;  // Include the parity bit
    if (parity_type == 0) {  // Even parity
        return (ones_count % 2 == 0);
    } else {  // Odd parity
        return (ones_count % 2 != 0);
    }
}

// Main function
int main() {
    int bit_pattern, parity_type;
    
    // Input bit pattern (assumed as an integer)
    printf("Enter the bit pattern (as an integer): ");
    scanf("%d", &bit_pattern);
    
    // Choose parity type
    printf("Enter parity type (0 for even, 1 for odd): ");
    scanf("%d", &parity_type);

    // Generate parity bit
    int parity_bit = generate_parity(bit_pattern, parity_type);
    printf("Generated Parity Bit: %d\n", parity_bit);

    // Simulate transmission (original data + parity bit)
    int received_pattern = (bit_pattern << 1) | parity_bit;
    printf("Transmitted Data (Including Parity Bit): %d\n", received_pattern);

    // Check parity at receiver side
    int received_data = received_pattern >> 1;  // Extract original data
    int received_parity = received_pattern & 1; // Extract parity bit

    if (check_parity(received_data, received_parity, parity_type)) {
        printf("No error detected.\n");
    } else {
        printf("Error detected in transmission!\n");
    }

    return 0;
}
