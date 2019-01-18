#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Laboratorio1.h"
#include "HashTable.h"
#include "FileManager.h"

bool booleanBuffer = false;
long previousItem = 0L;

/**
* Initialize the Hash Table and the Registers with size @param HASH_SIZE
*/
void initHashTable(bool first) {
    if(first) {
        hashArray = (struct HashItem*) calloc(HASH_SIZE + 1, sizeof(struct HashItem));
        recordTable(hashArray, HASH_SIZE + 1);
    }

    dummyItem = malloc(sizeof(struct HashItem));
    dummyNode = malloc(sizeof(struct Node));
    lastNode = malloc(sizeof(struct Node));
    prevDummyNode = malloc(sizeof(struct Node));
}

void dellocateMemory() {
    free(hashArray);
    free(dummyItem);
    free(dummyNode);
    free(lastNode);
    free(prevDummyNode);
}

void toLower(char *str) {
    for(; *str; ++str) *str = tolower(*str);
}

/**
 * DJB2 hash function over @param str char array
 */
unsigned long hash(char *str) {
    toLower(str);
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_SIZE;
}

void insert(struct DogType* dogType) {
    int position = hash(dogType->name);
    getHashItem(dummyItem, position);

    setFileIndicatorAtEnd();
    long reg = getCurrentPosition();

    dummyNode->key = position;
    mempcpy(&dummyNode->data, dogType, sizeof(struct DogType));
    dummyNode->position = reg;

    if(dummyItem == NULL || dummyItem->head == 0) {
        dummyNode->nextHashItem = 0L;
    } else {
        mempcpy(&dummyNode->nextHashItem, &dummyItem->head, sizeof(long));
    }

    mempcpy(&dummyItem->head, &dummyNode->position, sizeof(long));
    recordNodeInCurrentPosition(dummyNode);
    recordHashItem(dummyItem, position);

    if(firstReg <= 0) {
        setFirstRecord(reg);
    }

    setLastRecord(reg);
}

void search(char *key) {
    int position = hash(key);

    getHashItem(dummyItem, position);

    if(dummyItem == NULL || dummyItem->head == 0) {
        notifySearchFinished();
        //printf("Records not found.");
        return;
    }

    booleanBuffer = getNode(dummyNode, dummyItem->head);
    if(booleanBuffer == false) return;

    if(dummyNode->key == -1) {
        notifySearchFinished();
        //printf("Records not found.");
        dummyItem->head = dummyNode->nextHashItem;
        recordHashItem(dummyItem, position);
        return;
    } else if(strcmp(key, dummyNode->data.name) == 0) {
        notifyRecordFound(&dummyNode->data);
        //printDogType(&dummyNode->data);
        //printf("-------------------------------\n");
    } else {
        //printf("Names don't match\n");
    }

    if(dummyNode->nextHashItem == 0L) {
        notifySearchFinished();
        return;
    }

    previousItem = dummyNode->position;

    do {
        booleanBuffer = getNode(dummyNode, dummyNode->nextHashItem);
        if(dummyNode->key == -1) {
            getNode(prevDummyNode, previousItem);
            prevDummyNode->nextHashItem = dummyNode->nextHashItem;
            recordNode(prevDummyNode, previousItem);
        } else {
            if(strcmp(key, dummyNode->data.name) == 0) {
                notifyRecordFound(&dummyNode->data);
                //printDogType(&dummyNode->data);
                //printf("-------------------------------\n");
            } else {
                //printf("Names don't match\n");
            }
        }
        previousItem = dummyNode->position;
    } while(booleanBuffer == true && dummyNode->nextHashItem != 0L);
    notifySearchFinished();
}

void removeItem(struct Node* node) {
    node->key = -1;
    recordNode(node, node->position);
}

void printDogType(struct DogType* dogType) {
    printf("Name: %s\n", dogType->name);
    printf("Type: %s\n", dogType->type);
    printf("Age: %d\n", dogType->age);
    printf("Race: %s\n", dogType->race);
    printf("Height: %d\n", dogType->height);
    printf("Weight: %.2f\n", dogType->weight);
    printf("Sex: %d\n", dogType->sex);
}

void printTable() {
    for(int i = 0; i < HASH_SIZE; i++) {
        getHashItem(dummyItem, i);
        printf("%li - %c\n", dummyItem->head, 'c');
    }
}

void printFirstNodes(long quantity) {
    struct Node* node = (struct Node*) calloc(1, sizeof(struct Node));
    booleanBuffer = false;

    for(int i = 0; i < quantity; i++) {
        booleanBuffer = getNodeByEntryOrder(node, i);
        if(booleanBuffer == true) {
            printf("NODE: %d\nCurr.\t| Hash\t| Next\n %ld\t| %d\t| %ld\n\n", i,
                   node->position, node->key, node->nextHashItem);
            printDogType(&node->data);
            printf("-----------------------------\n");
        } else {
            break;
        }
    }

    free(node);
}
