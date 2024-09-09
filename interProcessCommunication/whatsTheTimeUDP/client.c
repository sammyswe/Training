#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>  
#include <netinet/in.h> 
#include <unistd.h>  
#include <sys/types.h>
#include <sys/socket.h>  
#define BUFFER_SIZE 1024 

int main(void){ 
    struct sockaddr_in server_addr;
    int sd;
    char buffer[BUFFER_SIZE];
    size_t bytes_received;
    socklen_t addr_len = sizeof(server_addr);

    // Create a UDP socket (SOCK_DGRAM)
    sd = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }//the client doesnt need to bind.

    // Set server address properties
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); 
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr));

    // Send registration signal to the server
    printf("Press R to register for time updates: ");
    fgets(buffer, sizeof(buffer), stdin);  

    if (buffer[0] == 'R') {
        // Send the 'R' request to the server using sendto()
        sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_len);

        // Receive time updates from the server
        while ((bytes_received = recvfrom(sd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_addr, &addr_len)) > 0) {
            buffer[bytes_received] = '\0';
            printf("The Current Date & Time is: %s", buffer);
        }
    }

    close(sd);
    return 0; 
}
