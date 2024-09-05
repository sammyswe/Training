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
    
    memset(&server_addr, 0, sizeof(server_addr)); //sets socket memory to 0 (clear)
    server_addr.sin_family = AF_INET; //uses ipv4 protocol.
    server_addr.sin_port = htons(8080); //chooses port, converts to network byte order.
    
    
    //server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    //the above line can use the inet_addr function, or it can use the function below. It is deprecated however,
    //as it only works for ipv4. Instead use pton function (presentation to network), which achieves the same function.

    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)); //127.0.0.1 is the loopback interface (communication between processes on same computer)

    //pton takes three parameters
    //1. af (address family) - AF_INET (ipv4)
    //2. src - adress to be converted into network readable address
    //3. destination - where to store this network readable address

 
    ret = connect(sd,(struct sockaddr*) &server_addr, sizeof(server_addr));

    file = fopen("sender.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        // Send the contents of the buffer
        int y = send(sd, buffer, bytesRead, 0);
        //send takes 4 parameters:
        //1. Socket Descriptor
        //2. pointer to the buffer (arrays are treated as pointers inherently)
        //3. length of the data to be sent
        //4. flags (this will just be set to 0 most of the time.)
        printf("Data sent successfully\n");
    }

    
    fclose(file);
    close(sd);

    return 0; 

}