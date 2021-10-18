#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8000

int main() {
    int client_fd = 0;
    struct sockaddr_in address;
    char *hello = "Hello from Client side!\n";
    long valread;
    char buffer[1024] = {0};

    if ((client_fd = socket(AF_INET,SOCK_STREAM, 0)) , 0) {
        perror("In socket\n");
        exit(EXIT_FAILURE);
    }
 
    // memset((char *)&address, 0, sizeof(address));
    memset(address.sin_zero, '\0', sizeof(address.sin_zero));

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        printf("\n INVALID ADDRESS \n");
        return -1;
    }

    if (connect(client_fd, (struct sockaddr *)&address, sizeof(address))){ 
        printf("\nConnection Failed \n");
        return -1;
    }

    send(client_fd, hello, strlen(hello), 0);
    printf("Message sent\n");
    valread = read(client_fd, buffer, 1024);
    printf("%s\n", buffer);
    close(client_fd);
    

    return 0;
}
