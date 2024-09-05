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
    int ret, sd;
    char buffer[BUFFER_SIZE];
    size_t bytes_received;

    sd = socket(AF_INET, SOCK_STREAM, 0); //define socket
    
    memset(&server_addr, 0, sizeof(server_addr)); //define socket properties
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(8080); 
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)); 
    
    ret = connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)); //send connection request to server

    printf("Press R to register for time updates: ");
    fgets(buffer, sizeof(buffer), stdin);  

    if (buffer[0] == 'R') { 
        int y = send(sd, buffer, strlen(buffer), 0); //send register signal 
        while ((bytes_received = recv(sd, buffer, sizeof(buffer), 0)) > 0) { 
            buffer[bytes_received] = '\0'; 
            printf("The Current Date & time is: %s", buffer); 
        }
    }

    close(sd);
    return 0; 
}
