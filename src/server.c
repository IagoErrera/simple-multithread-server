#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <pthread.h>

#include "utils/error_msg.h"

#define PORT 18000
#define MAX_DATA 4096
#define SOCKET_QUEUE 10

void* handle_connection(void* arg);

int main() {
    int server_fd, connection_fd;
    struct sockaddr_in server_addr;
    char server_addr_string[MAX_DATA + 1];
    char connection_addr_string[MAX_DATA + 1];

    // Create a IPv4 STREAM TCP Socket 
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) error_msg("Create socket error");

    int opt = 1;
    int set_socket_status = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (set_socket_status < 0) error_msg("Error on set socket");

    // Configuring the socket addrs
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(PORT);

    // Binding Socket to addrs
    int binding_status = bind(server_fd, (sockaddr*) &server_addr, sizeof(server_addr));
    if (binding_status < 0) error_msg("Binding socket error");

    // Turn socket able to receive connections
    int listen_status = listen(server_fd, SOCKET_QUEUE);
    if (listen_status < 0) error_msg("Set socket to listen error");

    inet_ntop(AF_INET, &server_addr, server_addr_string, MAX_DATA);
    printf("Listenning on %s\r\n\n", server_addr_string);
    
    fflush(stdout);

    int i = 0;

    while (true) {
        // Accept the first connection on the queue (wait if don't have connection on the queue) 
        struct sockaddr_in connection_addr;
        socklen_t connection_addr_len;
        
        printf("Waiting connection...\r\n");
        fflush(stdout);
        connection_fd = accept(server_fd, (sockaddr *) &connection_addr, &connection_addr_len);

        inet_ntop(AF_INET, &connection_addr, connection_addr_string, MAX_DATA);
        // printf("Connected with %s\r\n", connection_addr_string);
        printf("Connection %d\n\r", i++);
        fflush(stdout);
        

        int* p_fd = (int*)malloc(sizeof(int));
        *p_fd = connection_fd;
        pthread_t t;
        pthread_create(&t, NULL, handle_connection, p_fd);
        // handle_connection(p_fd);
    }

    close(server_fd);
}

void* handle_connection(void* arg) {
    int fd = *((int*)(arg));
    free(arg);

    char send_buff[MAX_DATA + 1];
    char receive_buff[MAX_DATA + 1];
    char actual_path[MAX_DATA + 1];
    int bytes_read;

    memset(receive_buff, 0, MAX_DATA);
    if (read(fd, receive_buff, MAX_DATA - 1) <= 0) {
        close(fd);
        error_msg("No data");
    }

    printf("Received: %s", receive_buff);

    char method[16], path[256], version[16];
    if (sscanf(strtok(receive_buff, "\n"), "%15s %255s %15s", method, path, version) != 3) {
        close(fd);
        error_msg("Failed to parse request line");
        return NULL;
    }

    printf("\n\r-----------------------\n\r");
    printf("Method: %s\n\r", method);
    printf("Path: %s\n\r", path);
    printf("Version: %s\n\r", version);
    printf("-----------------------\n\r");
    fflush(stdout);

    memmove(path, path + 1, strlen(path));

    if (realpath(path, actual_path) == NULL) {
        close(fd);
        error_msg("Path not found");
    }

    FILE* file = fopen(actual_path, "r");
    if (file == NULL) {
        close(fd);
        error_msg("Can't open file");
    }

    while ((bytes_read = fread(send_buff, sizeof(char), MAX_DATA, file)) > 0) {
        // printf("Sending: %s\n\r", (char*)send_buff);
        write(fd, send_buff, bytes_read);
    }

    // Simuling server processing  
    // usleep(100 * 1000);
    sleep(10);
    
    close(fd);
    fclose(file);
    printf("Closing connection\n\r\n\r");
    return NULL;
}