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
    int retval, new_sd, sd; 
    
    sd = socket(AF_INET, SOCK_STREAM, 0); //create socket
    
    memset(&server_addr, 0, sizeof(server_addr)); //clear socket -> define socket properties 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); 
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)); 

    retval = bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)); //link socket to socket properties
    retval = listen(sd, 10);//wait for connection request

    //check return value for debugging.


    socklen_t len = sizeof(client_addr); 
    new_sd = accept(sd, (struct sockaddr*)&client_addr, &len); //stores client address in new socket

    int bytes_received;
    char buffer[BUFFER_SIZE]; //buffer for data transfer

    // Wait for client's 'R' registration request
    while ((bytes_received = recv(new_sd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate the received data (safety)

        // Check if 'R' is present in the buffer
        if (strchr(buffer, 'R') != NULL) {
            printf("Client registered for time updates.\n");
            
            while (1) { //sends time indefinitely
                time_t current_time;
                time(&current_time); 
                char* readableTime = ctime(&current_time);

                snprintf(buffer, sizeof(buffer), "%s", readableTime);
                int y = send(new_sd, buffer, strlen(buffer), 0);
                printf("Current Date Time Sent :)\n");

                sleep(5);  // Wait 5 seconds before sending the next time update
            }
        }else{
            break;
        }
    }

    close(new_sd);
    close(sd);

    return 0;
}
