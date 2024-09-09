// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_CLIENTS 5 // once this number has been reached, draw lottery.
#define BUFFER_SIZE 1024
#define NUMBERS_RANGE 90

int main() {
    int server_fd, new_socket, client_sockets[MAX_CLIENTS], max_clients = MAX_CLIENTS;
    int collected_numbers[MAX_CLIENTS] = {0}; //sets all to 0
    struct sockaddr_in address;
    int addrlen = sizeof(address), opt = 1;
    char buffer[BUFFER_SIZE] = {0};
    fd_set readfds;
    srand(time(NULL));  // NULL creates different random sequence each time.

    // Initialize client sockets array to 0
    for (int i = 0; i < max_clients; i++) {
        client_sockets[i] = 0;
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
        

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //sets socket options
    //& opt allows reuse across many sockets
    //We can put multiple client sockets on 8080

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to the address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        exit(EXIT_FAILURE);
    }

    // Start listening for client connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        exit(EXIT_FAILURE);
    }

    printf("Lottery open and waiting for entrants...\n");

    while (1) {  

    // Clear the file descriptor set and reset it for select()
    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);

    int max_sd = server_fd; //consistently will be updated with highest socket descriptor value.
    
    for (int i = 0; i < max_clients; i++) { //loop through socket array
        int sd = client_sockets[i]; 
        // Adds valid socket descriptors to set
        if (sd > 0) FD_SET(sd, &readfds);
        if (sd > max_sd) max_sd = sd;
    }

    // select() waits for an activity on one of the monitored file descriptors
    // max_sd + 1 -> this ensures that we check all sds
    if (select(max_sd + 1, &readfds, NULL, NULL, NULL) < 0) {  // Wait indefinitely (NULL for timeout)
        perror("Select failed");  
        exit(EXIT_FAILURE); 
    }

    if (FD_ISSET(server_fd, &readfds)) {  // new incoming connection - store in new_socket
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");  
            exit(EXIT_FAILURE); 
        }
        // Find spot in client_socket array for new socket
        for (int i = 0; i < max_clients; i++) {
            if (client_sockets[i] == 0) {  
                client_sockets[i] = new_socket; 
                printf("New connection: Client %d connected\n", i + 1); //i+1 to count sockets from 1
                break;  
            }
        }
    }

    // Process incoming client messages
    for (int i = 0; i < max_clients; i++) { 
        int sd = client_sockets[i];  

        // loop through connected clients to check for message
        if (FD_ISSET(sd, &readfds)) {  
            int valread = read(sd, buffer, BUFFER_SIZE);  
            if (valread == 0) { //check for client disconnect
                printf("Client %d disconnected\n", i + 1); 
                close(sd);  
                client_sockets[i] = 0; //set socket status to free
            } else {
                buffer[valread] = '\0';  //ensure null termination
                int chosen_number = atoi(buffer);  
                collected_numbers[i] = chosen_number;  
                printf("Received number %d from Client %d\n", chosen_number, i + 1);  // Print Received lottery entrance

                // Check if all clients have sent their numbers
                int all_received = 1;  //this will be set to 0 if not all received.
                for (int j = 0; j < max_clients; j++) {
                    if (collected_numbers[j] == 0) {  
                        all_received = 0; 
                        break;  
                    }
                }
                if (all_received) {
                    int drawn_number = rand() % NUMBERS_RANGE + 1;  // Draw and print random number
                    printf("Randomly drawn number is %d\n", drawn_number); 
                    
                    int winner_index = -1;  //will be set to winners index if one of the entrants matches the drawn number
                    for (int j = 0; j < max_clients; j++) {  
                        if (collected_numbers[j] == drawn_number) {  
                            winner_index = j; 
                            break;  
                        }
                    }

                    
                    for (int j = 0; j < max_clients; j++) {  // Loop over all clients and prepare messages
                        char message[BUFFER_SIZE];  
                        if (winner_index == -1) {  //if there is no winner
                            snprintf(message, BUFFER_SIZE, "There was no winner. Winning number: %d\n", drawn_number);  // message for no winner
                        } else if (j == winner_index) {  // There is a winner which is this client; prepare message
                            snprintf(message, BUFFER_SIZE, "CONGRATULATIONS YOU ARE THE WINNER!!!!!!!!!!!! Winning number: %d!\n", collected_numbers[j]); 
                        } else {  //there is a winner but it is not this client; prepare message
                            snprintf(message, BUFFER_SIZE, "Unlucky, you lost, better luck next time. Winning number was %d\n", drawn_number); 
                        }
                        send(client_sockets[j], message, strlen(message), 0);  // deliver messages
                    }
                }
            }
        }
    }
}

return 0; 

}