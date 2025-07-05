#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define POLY 0x1021   // CRC-CCITT polynomial (x^16 + x^12 + x^5 + 1)
#define INIT_CRC 0xFFFF  // Initial CRC value

// Function to compute CRC-16 (CCITT)
uint16_t compute_crc16(uint8_t *data, size_t length) {
    uint16_t crc = INIT_CRC;
    
    for (size_t i = 0; i < length; i++) {
        crc ^= (data[i] << 8);  // XOR with high byte of CRC
        for (int j = 0; j < 8; j++) {  // Process each bit
            if (crc & 0x8000) {  // If MSB is 1, shift and XOR with polynomial
                crc = (crc << 1) ^ POLY;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;  // Return computed CRC-16 value
}

// Function to append CRC to data
void append_crc(uint8_t *data, size_t length, uint8_t *encoded) {
    memcpy(encoded, data, length);  // Copy original data
    uint16_t crc = compute_crc16(data, length);  // Compute CRC

    encoded[length] = (crc >> 8) & 0xFF;  // High byte of CRC
    encoded[length + 1] = crc & 0xFF;  // Low byte of CRC
}

// Function to verify received data
int verify_crc(uint8_t *received, size_t length) {
    return compute_crc16(received, length) == 0;  // If CRC is 0, no error detected
}

// Main function
int main() {
    uint8_t data[] = "HELLO";  // Input message
    size_t data_len = strlen((char *)data);
    uint8_t encoded[data_len + 2];  // Data + CRC

    // Generate CRC and encode data
    append_crc(data, data_len, encoded);

    // Print encoded data with CRC
    printf("Encoded Data (Hex): ");
    for (size_t i = 0; i < data_len + 2; i++) {
        printf("%02X ", encoded[i]);
    }
    printf("\n");

    // Case A: Without Error (Original Data)
    if (verify_crc(encoded, data_len + 2)) {
        printf("Verification (Without Error): No error detected.\n");
    } else {
        printf("Verification (Without Error): Error detected!\n");
    }

    // Case B: With Error (Simulating a corrupted bit)
    encoded[1] ^= 0x01;  // Introduce an error by flipping a bit

    if (verify_crc(encoded, data_len + 2)) {
        printf("Verification (With Error): No error detected.\n");
    } else {
        printf("Verification (With Error): Error detected in transmission!\n");
    }

    return 0;
}
