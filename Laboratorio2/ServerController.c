#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include <strings.h>

#include "Laboratorio1.h"
#include "ServerController.h"
#include "HashTable.h"

int socketServer = 0, socketClient = 0;
int bufferInt;

void initServer() {
    if((socketServer = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        HANDLE_ERROR("Socket does not created.");
        return;
    }

    int option = 1;
    setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    dummyAddr.sin_family = AF_INET;
    dummyAddr.sin_addr.s_addr = INADDR_ANY;
    dummyAddr.sin_port = htons(8888);

    if(bind(socketServer, (struct sockaddr*) &dummyAddr, sizeof(dummyAddr)) != 0) {
        HANDLE_ERROR("Error while binding the socket with address and port.");
        return;
    }

    if(listen(socketServer, MAX_CLIENTS) != 0) {
        HANDLE_ERROR("Error while listening.");
        return;
    }
}

bool acceptConnection() {
    addrlen = sizeof(dummyAddr);
    socketClient = accept(socketServer, (struct sockaddr*) &dummyAddr, &addrlen);

    if(socketClient == -1) {
        HANDLE_ERROR("Error accepting the connection.");
        memset(ipDirection, -1, sizeof(ipDirection));
        return false;
    }

    ipv4Addr = (struct sockaddr_in*)&dummyAddr;
    ipAddr = ipv4Addr->sin_addr;

    inet_ntop(AF_INET, &ipAddr, ipDirection, sizeof(ipDirection));

    return true;
}

void receiveMessage(void *pointer, size_t len) {
    if((bytesRead = read(socketClient, pointer, len)) <= 0) {
        HANDLE_ERROR("Error receiving menu option");
    }
}

void sendFile(char* name, size_t len) {
    sendMessage(name, len);

    if((tempFile = fopen(name, "r")) == NULL) {
        char err = -1;
        sendMessage(&err, sizeof(char));
    } else {
        if(fseek(tempFile, 0, SEEK_END) != 0) {
            HANDLE_ERROR("File manipulation failed.");
            return;
        }

        int lenght = ftell(tempFile);
        rewind(tempFile);

        do {
            if(fread(buffer, (lenght < SIZE_CHUNK) ? lenght : SIZE_CHUNK, 1, tempFile) <= 0){
                HANDLE_ERROR("Error reading the file.");
                return;
            }

            sendMessage(buffer, (lenght < SIZE_CHUNK) ? lenght : SIZE_CHUNK);
            lenght -= SIZE_CHUNK;
        } while(lenght >= 0);

        #ifdef VERBOSE_MODE
        printf("File sent successfully\n");
        #endif // VERBOSE_MODE
        fclose(tempFile);
    }
}

void receiveFile() {
    receiveMessage(&fileName, 100);
    #ifdef VERBOSE_MODE
    printf("%s\n", fileName);
    #endif // VERBOSE_MODE

    if((tempFile = fopen(fileName, "w+")) == NULL) {
        HANDLE_ERROR("Error creating file.");
        return;
    }

    do {
        bzero(buffer, SIZE_CHUNK);
        bytesRead = recv(socketClient, buffer, SIZE_CHUNK, 0);
        fwrite(buffer, bytesRead, 1, tempFile);
    } while(bytesRead == SIZE_CHUNK);

    #ifdef VERBOSE_MODE
    printf("End of file receiving.\n");
    #endif // VERBOSE_MODE

    fclose(tempFile);
}

void sendMessage(void* message, size_t len) {
    if((bytesSent = send(socketClient, message, len, 0)) == -1) {
        HANDLE_ERROR("Error sending message.");
        return;
    }
    #ifdef VERBOSE_MODE
    printf("Message sent.\n");
    #endif // VERBOSE_MODE
}

char *getClientIp() {
    if(ipDirection[0] == -1) return NULL;
    return ipDirection;
}

void closeConnection() {
    if(close(socketClient) != 0) {
        HANDLE_ERROR("Error closing client socket.");
        return;
    }
}

void closeServer() {
    if(close(socketServer) != 0) {
        HANDLE_ERROR("Error closing server socket.");
        return;
    }
}
