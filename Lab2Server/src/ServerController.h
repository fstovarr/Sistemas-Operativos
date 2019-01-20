#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#define MAX_CLIENTS 32
#define SIZE_CHUNK 1024

extern int socketServer, socketClient;
extern int bufferInt;

char buffer[SIZE_CHUNK];
char fileName[100];
char ipDirection[INET_ADDRSTRLEN];

FILE *tempFile;

ssize_t bytesRead, bytesSent;
socklen_t addrlen;

struct sockaddr_in dummyAddr;
struct sockaddr_in* ipv4Addr;
struct in_addr ipAddr;

void initServer();
bool acceptConnection();
void closeConnection();
void closeServer();

void sendMessage(void* message, size_t len);
void receiveMessage(void *pointer, size_t len);

void sendFile(char* name, size_t len);
void receiveFile();

char *getClientIp();
