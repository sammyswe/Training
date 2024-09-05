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
    
 
    struct sockaddr_in server_addr, client_addr; //sockaddr in makes it easier to set up the parameters of the server, because we can give them in human readable format.
    int retval, new_sd, sd;
    sd = socket(AF_INET, SOCK_STREAM,0); //this is a socket descriptor (identifies socket by a unique int given to it)
    FILE *file;
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    memset(&server_addr, 0, sizeof(server_addr)); //sets all memory of socket to 0.
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

    retval = bind(sd,(struct sockaddr*)&server_addr, sizeof(server_addr)); //the bind function takes a sockaddr, instead of sockaddr_in, so we cast the pointer.
    retval = listen(sd,10);
    //bind links the socket descriptor to the socket address -> it gives the socket descriptor all of this info. Returns -1 if bind fails.
    //listen waits for a connection request from a client. Takes a socket descriptor and backlog (5 or 10 usually)

    socklen_t len = sizeof(client_addr);
    new_sd = accept(sd, (struct sockaddr*) &client_addr, &len);
    //accept waits for an incoming connection request from the client, and then stores this information into a new socket, returning this descriptor.


    // Open the file to write the received data
    file = fopen("receiver.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        close(new_sd);
        close(sd);
        exit(1);
    }

    // Receive data from the client and write to the file
    int bytes_received;
    while ((bytes_received = recv(new_sd, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, sizeof(char), bytes_received, file);  // Write received data to the file
        fflush(file);  // Ensure data is flushed to the file immediately
    }

    if (bytes_received == 0) {
        printf("Data Received Successfully\n");
    } else if (bytes_received < 0) {
        perror("Data Transfer Failed\n");
    }

    // Close the file and sockets
    fclose(file);
    close(new_sd);
    close(sd);

    return 0;
}