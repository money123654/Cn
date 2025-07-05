#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void write_file(int sockfd) {
    int n;
    FILE *fp;
    char buffer[BUFFER_SIZE];

    fp = fopen("received_file.txt", "w");
    if (fp == NULL) {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while (1) {
        n = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (n <= 0){
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, BUFFER_SIZE);
    }
    printf("[+]File received successfully.\n");
    fclose(fp);
    return;
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char filename[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Client socket created.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    printf("Enter the filename to request: ");
    scanf("%s", filename);
    send(sockfd, filename, strlen(filename), 0);

    write_file(sockfd);

    close(sockfd);
    printf("[+]Disconnected from server.\n");

    return 0;
}
