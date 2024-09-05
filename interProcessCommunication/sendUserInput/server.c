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
    

    struct sockaddr_in server_addr, client_addr; 
    int retval, new_sd, sd; 
    sd = socket(AF_INET, SOCK_STREAM,0); 
    FILE *file;
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    

    memset(&server_addr, 0, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); 
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)); 


    retval = bind(sd,(struct sockaddr*)&server_addr, sizeof(server_addr)); 
    retval = listen(sd,10);

    socklen_t len = sizeof(client_addr);
    new_sd = accept(sd, (struct sockaddr*) &client_addr, &len);

    int bytes_received;
    while ((bytes_received = recv(new_sd, buffer, sizeof(buffer), 0)) > 0) { //while the client hasnt closed the connection
        
        buffer[bytes_received] = '\0';// Null-terminate the received data to safely print it as a string
        printf("\n");
        printf("%s", buffer); 
        printf("\n");
    }



    close(new_sd);
    close(sd);

    return 0;
}