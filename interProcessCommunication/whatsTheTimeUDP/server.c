#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>  
#include <netinet/in.h> 
#include <unistd.h>  
#include <sys/types.h>
#include <sys/socket.h>   
#include <time.h>
#define BUFFER_SIZE 1024 

int main(void){ 
    struct sockaddr_in server_addr, client_addr; 
    int sd;
    char buffer[BUFFER_SIZE]; 
    socklen_t client_len = sizeof(client_addr);
    int bytes_received;
    //udp connection, bind on both side

 
    sd = socket(AF_INET, SOCK_DGRAM, 0); //sock DGRAM is a UDP connection
  

    // Set server address properties
    memset(&server_addr, 0, sizeof(server_addr)); //sets all memory in server address to 0
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // the server will listen for any datagrams sent to 127.0.0.1 port 8080, and when it receives one 
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)); //it notes down the port

    // Bind the socket to the server address
    if (bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) { //binds socket descriptor to server properties.
        perror("Bind failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    // Wait for client's 'R' registration request
    while ((bytes_received = recvfrom(sd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &client_len)) > 0) {
        //receive from function obtains the client address when it first receives a message (IP address and port number)
        buffer[bytes_received] = '\0'; // Null-terminate the received data

        // Check if 'R' is present in the buffer
        if (strchr(buffer, 'R') != NULL) {
            printf("Client registered for time updates.\n");

            // Send the time periodically
            while (1) {
                time_t current_time;
                time(&current_time);
                char* readableTime = ctime(&current_time);

                snprintf(buffer, sizeof(buffer), "%s", readableTime);
                sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, client_len);
                printf("Current Date Time Sent :)\n");

                sleep(5);  // Wait 5 seconds before sending the next update
            }
        }
    }

    close(sd);
    return 0;
}
