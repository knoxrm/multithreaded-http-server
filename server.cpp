#include <cstring>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000
#define SERVER_BACKLOG 1


void errorHandler(char * msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

//void* handleConnection(void* arg) {
    //int* socket_ptr = (int *)arg;
    //int clientSocket = *socket_ptr;
    //free(socket_ptr);
void handleConnection(int clientSocket) {
    long valread;
    char buffer[1024] = {0};
    char *httpMsg = "HTTP/1.0 200 OK\r\n\r\nHello from the server side!\n";
    if((valread = read(clientSocket, buffer, 1024)) < 0) 
        errorHandler("Unable to read socket");


    printf("%s", buffer);
    send(clientSocket, httpMsg, strlen(httpMsg),0);
    printf("message sent\n");
    memset(buffer, 0, sizeof(buffer));
    close(clientSocket);
    // return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET,SOCK_STREAM, 0)) , 0) {
        perror("In socket\n");
        exit(EXIT_FAILURE);
    }
 
    // memset(address.sin_zero, '\0', sizeof(address.sin_zero));
    bzero(&address, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
        errorHandler("bind failed");

    printf("Server started .....\n");

    if (listen(server_fd, SERVER_BACKLOG) < 0) 
        errorHandler("Error in Listen");

    while (1) {
        printf("Waiting for a connection.....\n");
        if ((new_socket = accept(server_fd,
                        (struct sockaddr *)&address,
                        (socklen_t*)&addrlen)) < 0) 
            errorHandler("Error in accept");
        
         // handleConnection(new_socket);
        //pthread_t socketThread;
        //int* clientArg = (int *)malloc(sizeof(int));
        //*clientArg = new_socket;
        //pthread_create(&socketThread, NULL, handleConnection, clientArg);
    }
    close(server_fd);

    return 0;
}
