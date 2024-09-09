// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }


    int chosen_number;
    printf("Enter your chosen number (1-90): ");
    scanf("%d", &chosen_number);
    sprintf(buffer, "%d", chosen_number); //places the number in string format in buffer
    send(sock, buffer, strlen(buffer), 0); // sends to server
    printf("Sent number %d to the server\n", chosen_number);

    // Wait for the result from the server
    valread = read(sock, buffer, BUFFER_SIZE);
    buffer[valread] = '\0';
    printf("%s\n", buffer); //prints it to the clients tream


    close(sock);
    return 0;
}
