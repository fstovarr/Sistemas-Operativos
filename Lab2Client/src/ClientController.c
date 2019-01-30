#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "ClientController.h"
#include "main.h"

int socketClient = 0;

void requestConnection() {
    if((socketClient = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        HANDLE_ERROR("Socket does not created.");
        return;
    }

    dummyAddr.sin_addr.s_addr = inet_addr(IP_SERVER);
    dummyAddr.sin_family = AF_INET;
    dummyAddr.sin_port = htons(8888);

    while(connect(socketClient, (struct sockaddr*) &dummyAddr, sizeof(dummyAddr)) != 0) {
        HANDLE_ERROR("Trying to connect to server... ");
        sleep(TIME_TO_RECONNECT);
    }

    printf("Connection successfully\n");
}

void sendMessage(void* message, size_t len) {
    if((bytesSent = send(socketClient, message, len, 0)) == -1) {
        HANDLE_ERROR("Error sending message.");
        return;
    }
}

void receiveMessage(void* message, size_t len) {
    if((bytesRead = recv(socketClient, message, len, 0)) <= 0) {
        HANDLE_ERROR("Error reading bytes");
    }
}

char* receiveFile() {
    #ifdef VERBOSE_MODE
    printf("Reading the file: ");
    #endif // VERBOSE_MODE
    receiveMessage(&fileName, sizeof(fileName));

    #ifdef VERBOSE_MODE
    printf("%s\n", fileName);
    #endif // VERBOSE_MODE

    if((file = fopen(fileName, "w+")) == NULL) {
        HANDLE_ERROR("Error creating file.");
    }

    do {
        bzero(buffer, SIZE_CHUNK);
        bytesRead = recv(socketClient, buffer, SIZE_CHUNK, 0);
        if(buffer[0] == -1){
            printf("Empty file\n");
            break;
        }
        fwrite(buffer, bytesRead, 1, file);
    } while(bytesRead == SIZE_CHUNK);

    #ifdef VERBOSE_MODE
    printf("End file read\n");
    #endif // VERBOSE_MODE

    fclose(file);

    return fileName;
}

void sendFileUpdated(char *name, size_t len) {
    sendMessage(name, len);

    bool isEmptyFile = true;

    char *content = NULL;
    if((file = fopen(name, "r")) == NULL) {
        HANDLE_ERROR("File does not exists.");
        sendMessage(&isEmptyFile, sizeof(bool));
    } else {
        if(fseek(file, 0, SEEK_END) != 0) {
            HANDLE_ERROR("File manipulation failed.");
            return;
        }

        //sendMessage(&isEmptyFile, sizeof(bool));

        int lenght = ftell(file);
        rewind(file);

        if(fread(buffer, (lenght < SIZE_CHUNK) ? lenght : SIZE_CHUNK, 1, file) <= 0){
            HANDLE_ERROR("Error reading the file. (out loop)");
            sendMessage(&isEmptyFile, sizeof(bool));
            return;
        }

        isEmptyFile = false;
        sendMessage(&isEmptyFile, sizeof(bool));

        sendMessage(buffer, (lenght < SIZE_CHUNK) ? lenght : SIZE_CHUNK);
        lenght -= SIZE_CHUNK;

        while(lenght >= 0) {
            if(fread(buffer, (lenght < SIZE_CHUNK) ? lenght : SIZE_CHUNK, 1, file) <= 0){
                HANDLE_ERROR("Error reading the file. (in loop)");
                return;
            }

            sendMessage(buffer, (lenght < SIZE_CHUNK) ? lenght : SIZE_CHUNK);
            lenght -= SIZE_CHUNK;
        }

        #ifdef VERBOSE_MODE
        printf("File sent successfully\n");
        #endif // VERBOSE_MODE
    }
}

void closeConnection() {
    if(close(socketClient) != 0) {
        HANDLE_ERROR("Error closing socket");
        return;
    }
}
