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
    FILE *file;
    char buffer [BUFFER_SIZE];
    size_t bytesRead;

    sd = socket(AF_INET, SOCK_STREAM,0); 
    
    memset(&server_addr, 0, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(8080); 
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)); 
    
    ret = connect(sd,(struct sockaddr*) &server_addr, sizeof(server_addr));

    printf("Input the string you want to transfer: ");
    fgets(buffer, sizeof(buffer), stdin);  

    int y = send(sd, buffer, strlen(buffer), 0);  
    
    close(sd);

    return 0; 

}