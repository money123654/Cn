#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(FILE *fp, int sockfd) {
    char data[BUFFER_SIZE] = {0};

    while(fgets(data, BUFFER_SIZE, fp) != NULL) {
        if (send(sockfd, data, strlen(data), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, BUFFER_SIZE);
    }
}

int main() {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    char filename[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding success.\n");

    if(listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    } else {
        perror("[-]Error in listening");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    if(new_sock < 0) {
        perror("[-]Error in accepting");
        exit(1);
    }

    recv(new_sock, filename, BUFFER_SIZE, 0);
    printf("[+]Requested file: %s\n", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("[-]Error in reading file.");
        exit(1);
    }

    send_file(fp, new_sock);
    printf("[+]File data sent successfully.\n");

    close(new_sock);
    close(sockfd);

    return 0;
}
