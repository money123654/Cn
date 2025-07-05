#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 30  // Maximum capacity of the bucket
#define OUTPUT_RATE 10  // Rate at which packets are sent out

void leakyBucket(int input_packets[], int num_packets) {
    int bucket_content = 0;  // Current content in the bucket
    int i;

    printf("Time\tReceived\tSent\tDropped\tBucket Content\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < num_packets; i++) {
        int received = input_packets[i];
        int sent = 0;
        int dropped = 0;

        // Add packets to the bucket
        if (received + bucket_content > BUCKET_SIZE) {
            dropped = (received + bucket_content) - BUCKET_SIZE;  // Dropped packets
            bucket_content = BUCKET_SIZE;  // Bucket is full
        } else {
            bucket_content += received;  // Add packets to the bucket
        }

        // Send packets at the output rate
        if (bucket_content > 0) {
            sent = (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE;
            bucket_content -= sent;
        }

        // Display the results
        printf("%d\t%d\t\t%d\t%d\t%d\n", i + 1, received, sent, dropped, bucket_content);
    }
}

int main() {
    int num_packets;

    // Input the number of packets
    printf("Enter the number of packets: ");
    scanf("%d", &num_packets);

    int input_packets[num_packets];

    // Input the size of each packet
    printf("Enter the size of each packet:\n");
    for (int i = 0; i < num_packets; i++) {
        printf("Packet %d: ", i + 1);
        scanf("%d", &input_packets[i]);
    }

    // Simulate the leaky bucket algorithm
    leakyBucket(input_packets, num_packets);

    return 0;
}
