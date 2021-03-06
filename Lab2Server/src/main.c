#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "main.h"
#include "HashTable.h"
#include "FileManager.h"
#include "Tests.h"
#include "ServerController.h"
#include "Logger.h"

#define VERBOSE_MODE

long firstReg = -1;
long lastReg = -1;

void initProcess() {
    dummyPet = (struct DogType*) malloc(sizeof(struct DogType));

    bool firstTime = initFile();
    loadFirstRecord();
    loadLastRecord();
    initHashTable(firstTime);
    initLogger();

    if(firstTime) {
        fillWithRandomAnimals();
    }
}

/**
 * Función donde se solicitan datos y almacenan
 */
void enterRecord() {
    receiveMessage(dummyPet, sizeof(struct DogType));
    insert(dummyPet);
    registerOperation(getClientIp(), INSERTION, dummyPet->name, sizeof(dummyPet->name));
}

void showRecord() {
    int rec;
    receiveMessage(&rec, sizeof(int));

    struct Node* node = (struct Node*) calloc(1, sizeof(struct Node));
    if(rec >= 0 && getNodeByEntryOrder(node, rec) == true && node->key != -1) {
        char *name = (char*) calloc(1, 100);

        sendMessage(&rec, sizeof(int));
        buildName(node->data.name, rec + 1, name);
        sendFile(name, 100);
        receiveFile();

        free(name);
    } else {
        rec = -1;
        sendMessage(&rec, sizeof(int));
    }

    free(node);
    registerIntOperation(getClientIp(), READING, rec);
}

void deleteRecord() {
    int rec;
    receiveMessage(&rec, sizeof(int));

    struct Node* node = (struct Node*) calloc(1, sizeof(struct Node));
    char *name = (char*) malloc(100);

    #ifdef VERBOSE_MODE
    printf("Deletion finished.\n");
    #endif // VERBOSE_MODE

    if(getNodeByEntryOrder(node, rec) == true && node->key != -1) {
        #ifdef VERBOSE_MODE
        printf("Deletion finished.\n");
        #endif // VERBOSE_MODE
        buildName(node->data.name, rec + 1, name);
        deleteFile(name);
        #ifdef VERBOSE_MODE
        printf("Deletion finished.\n");
        #endif // VERBOSE_MODE
        removeItem(node);
        sendMessage(&rec, sizeof(int));
        #ifdef VERBOSE_MODE
        printf("Deletion finished.\n");
        #endif // VERBOSE_MODE
    } else {
        rec = -1;
        sendMessage(&rec, sizeof(int));
    }

    registerIntOperation(getClientIp(), DELETION, rec);

    #ifdef VERBOSE_MODE
    printf("Deletion finished.\n");
    #endif // VERBOSE_MODE

    free(node);
    free(name);
}

void searchRecord() {
    char nm[32];
    receiveMessage(nm, sizeof(nm));
    search(nm);
    registerOperation(getClientIp(), READING, nm, sizeof(nm));
}

void notifySearchFinished() {
    dummyPet->age = -1;
    sendMessage(dummyPet, sizeof(struct DogType));
}

void notifyRecordFound(struct DogType *pet) {
    #ifdef VERBOSE_MODE
    printDogType(pet);
    #endif // VERBOSE_MODE
    sendMessage(pet, sizeof(struct DogType));
}

void closeProgram() {
    closeFile();
    exit(0);
}

void buildName(char* nm, int res, char* ans) {
    char it[12];
    sprintf(it, "%d", res);

    strcpy(ans, FOLDER_NAME);
    strcat(ans, it);
    strcat(ans, nm);
    strcat(ans, ".txt");
}

char* subString (const char* input, int offset, int len, char* dest) {
  int input_len = strlen (input);

  if (offset + len > input_len) {
   return NULL;
}

strncpy (dest, input + offset, len);
return dest;
}

void selectOption(int option) {
    #ifdef VERBOSE_MODE
    printf("Option selected: %d\n", option);
    #endif // VERBOSE_MODE

    switch(option){
        case 1:
        enterRecord();
        break;
        case 2:
        showRecord();
        break;
        case 3:
        deleteRecord();
        break;
        case 4:
        searchRecord();
        break;
        case 5:
            #ifdef VERBOSE_MODE
        printf("Closing connection.\n");
            #endif // VERBOSE_MODE
        break;
        case 6:
        printTable();
        break;
        case 7:
        printf("First record: %ld - Last record: %ld\n", firstReg, lastReg);
        printFirstNodes(5);
        break;
        default:
            #ifdef VERBOSE_MODE
        HANDLE_ERROR("Not valid option.");
            #endif // VERBOSE_MODE
        break;
    }
}

int main() {
    initProcess();
    initServer();
    #ifdef VERBOSE_MODE
    printf("Wating for connection...\n");
    #endif // VERBOSE_MODE
    int option = 0;

    while(true) {
        while(acceptConnection()) {
        #ifdef VERBOSE_MODE
            printf("Client connected successfully\n");
        #endif // VERBOSE_MODE

            while(option != 5) {
                receiveMessage(&option, sizeof(int));
                selectOption(option);
            }

            option = 0;
        }
    }
}

long calcRecordNumber() {
    return (lastReg - sizeof(long) * 2 - sizeof(struct HashItem) * HASH_SIZE) / sizeof(struct Node);
}

void setFirstRecord(long first) {
    firstReg = first;
    recordFirstRecord();
}

void setLastRecord(long last) {
    lastReg = last;
    recordLastRecord();
}
