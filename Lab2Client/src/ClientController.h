#define IP_SERVER "127.0.0.1"

// ------ Don't touch any line below that ----- //

#include <stdio.h>
#include <netinet/in.h>

#define TIME_TO_RECONNECT 1
#define SIZE_CHUNK 1024

extern int socketClient;

char buffer[SIZE_CHUNK];
char fileName[100];

FILE* file;

struct sockaddr_in dummyAddr;
ssize_t bytesSent, bytesRead;

void requestConnection();
void closeConnection();

void sendMessage(void* message, size_t len);
void receiveMessage(void* message, size_t len);

char* receiveFile();
void sendFileUpdated(char *name, size_t len);

long getFirstReg();
long getLastReg();
