#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include "BloomFilter.h"
#include "NumHashFunc.h"


using namespace std;

#define SERVER_PORT 5555 //Obviously the port of the server
#define QUEUE_LENGTH 5 //The maximum length of the queue of pending connections.
// (in other words, we can have QUEUE_LENGTH incoming connection request from different clients, and still remember all of them and handle them later once we can. if we have more than 5 of those, we might not remember to come back to some of the extra)
#define BUFFER_SIZE 4096
BloomFilter *bloomFilter;
// A function that handles communicating with the client in another thread, after it is accepted.
void *handle_client(void *arg) {
    // we must use void* here since it is automatically called from the function that creates new threads.

    int client_sock = *((int *)arg);

    // Note to Ariel:
    // I didn't really understand if we are supposed to create a unique bloom filter for each accepted request (if that is the case, it should happen right here!)
    // Or if we have 1 bloom filter for this entire tcp server. We need to ask someone that did it once it is relevant.

    // Continue with the communication until the client is done:
    while (1) {
        char buffer[BUFFER_SIZE]; 

        int read_bytes = recv(client_sock, buffer, sizeof(buffer), 0); //Recieve data from the client, and put it in the buffer.
        if (read_bytes == 0) {
            break; // Once the client sends an empty message, we understand it is done with its requests.

        } else if (read_bytes < 0) { //Check if there was an error during the communication:
            // If there was a problem, we close the client socket, and kill this thread:
            perror("error receiving from client");
            close(client_sock);
            pthread_exit(NULL); // (kills the current thread)

        } else { // We got valid data from the client:
            // This is currently an echo server, so we just printed what we got from the client. 
            // Later we can talk to the bloom filter according to the reqst from the user.
            bloomFilter->dealWithLine(buffer);
            // Echo back to the client:
            int sent_bytes = send(client_sock, buffer, read_bytes, 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
                close(client_sock);
                pthread_exit(NULL);
            }
        }
    }

    // Close the client socket and this thread after communication ends:
    close(client_sock);
    pthread_exit(NULL);
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // Check that the server socket was created successfully:
    if (sock < 0) { 
        perror("error creating socket");
    }
    std::vector<HashFunc*> hashFuncs{new NumHashFunc(256,1),new NumHashFunc(256,2),new NumHashFunc(256,3)};
    bloomFilter = new BloomFilter(256,  hashFuncs);


    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); // make every field of sin a zero.
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    // Try binding the socket after filling its fields:
    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    // Change the socket to listen mode:
    if (listen(sock, QUEUE_LENGTH) < 0) {
        perror("error listening to a socket");
    }

    // The server continuously waits for a client to connect to it:
    while(1) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);

        // We allocate the client socket id in the heap, and fill it once we accept a connection:
        int *client_sock = (int *)malloc(sizeof(int));
        *client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len);
        if (*client_sock < 0) { // Make sure it was successful:
            perror("error accepting client");
            free(client_sock);
            return 1;
        }

        pthread_t tid;
        // Start a new thread that has the client socket, and starts by running handle_client. Its id is saved in tid.
        if (pthread_create(&tid, NULL, handle_client, (void *)client_sock) != 0) {           
            // If we found a problem, just skip this connection and go handle the next one:
            perror("error creating thread");
            close(*client_sock);
            free(client_sock);

            continue;;
        }

        // From what I understand, we use this so that once the new thread finishes, it's resources will be cleaned for us by the system:
        pthread_detach(tid);
    }
            
    close(sock);
    return 0;
}