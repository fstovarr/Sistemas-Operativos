#include <stdio.h>

#include "main.h"
#include "HashTable.h"
#include "FileManager.h"

//#define VERBOSE_MODE

bool initFile() {
    file = fopen(FILE_NAME, "rb+");
    if(file == NULL) {
        file = fopen(FILE_NAME, "wb+");
        if(file == NULL) {
            #ifdef VERBOSE_MODE
            HANDLE_ERROR("Error opening/creating file.");
            #endif // VERBOSE_MODE
            return false;
        } else {
            fclose(file);
            file = fopen(FILE_NAME, "rb+");
            #ifdef VERBOSE_MODE
            printf("File created succesfully\n");
            #endif // VERBOSE_MODE
            return true;
        }
    } else {
        #ifdef VERBOSE_MODE
        printf("Records loaded succesfully\n");
        #endif // VERBOSE_MODE
        return false;
    }
}

void closeFile() {
    fclose(file);
}

long calcNodePosition(long nodePos) {
    return sizeof(long) * 2 + sizeof(struct HashItem) * HASH_SIZE + sizeof(struct Node) * nodePos;
}

long calcHashItemPosition(long hashItemPos) {
    return sizeof(long) * 2 + sizeof(struct HashItem) * hashItemPos;
}

void recordNode(struct Node* node, long position) {
    setFileIndicator(position);

    if(fwrite(node, sizeof(struct Node), 1, file) <= 0) {
        HANDLE_ERROR("Write node failed.");
    }
}

void recordNodeInCurrentPosition(struct Node* node) {
    if(fwrite(node, sizeof(struct Node), 1, file) <= 0) {
        HANDLE_ERROR("Write node failed.");
    }
}

/**
 * Get HashItem, that contains the head's linked list position
 * for the elements in this Hash slot.
 * @param item returns the HashItem in @param position or NULL if not exists.
 */
void getHashItem(struct HashItem* item, long position) {
    setFileIndicator(calcHashItemPosition(position));

    if(fread(item, sizeof(struct HashItem), 1, file) <= 0) {
        HANDLE_ERROR("Read hash table failed.");
    }
}

/**
 * Record HashItem, that contains the head's linked list position
 * for the elements in this Hash slot.
 * @param item is recorded in @param position.
 */
void recordHashItem(struct HashItem* item, long position) {
    setFileIndicator(calcHashItemPosition(position));

    if(fwrite(item, sizeof(struct HashItem), 1, file) <= 0) {
        HANDLE_ERROR("Write hash table failed.");
    }
}

void recordHashItemInCurrentPosition(void* item) {
    if(fwrite(item, sizeof(struct HashItem), 1, file) <= 0) {
        HANDLE_ERROR("Error writing hash item");
    }
}

void recordTable(struct HashItem* hashArray, int hashSize) {
    if(fwrite(hashArray, sizeof(struct HashItem) * hashSize, 1, file) > 0) {
        #ifdef VERBOSE_MODE
        printf("Hash table initialized\n");
        #endif // VERBOSE_MODE
    } else {
        HANDLE_ERROR("Hash table initialization failed):");
    }
}

void setFileIndicator(long position) {
    if(fseek(file, position, SEEK_SET) < 0) {
        HANDLE_ERROR("Error trying to set file indicator at custom position");
    }
}

void setFileIndicatorAtEnd() {
    if(fseek(file, 0L, SEEK_END) < 0) {
        HANDLE_ERROR("Error trying to set file indicator at end");
    }
}

void resetFileIndicator() {
    rewind(file);
}

bool getNodeByEntryOrder(struct Node* node, long position) {
    setFileIndicator(calcNodePosition(position));

    if(fread(node, sizeof(struct Node), 1, file) <= 0) {
        HANDLE_ERROR("Read hash table failed.");
        return false;
    }
    return true;
}

bool getNode(struct Node* node, long position) {
    setFileIndicator(position);

    if(fread(node, sizeof(struct Node), 1, file) <= 0) {
        HANDLE_ERROR("Read hash table failed.");
        return false;
    }
    return true;
}

long getCurrentPosition() {
    return ftell(file);
}

void loadFirstRecord() {
    if(fread(&firstReg, sizeof(long), 1, file) <= 0) {
        #ifdef VERBOSE_MODE
        HANDLE_ERROR("Error reading first register");
        #endif // VERBOSE_MODE
    }
}

void loadLastRecord() {
    setFileIndicator(sizeof(long));

    if(fread(&lastReg, sizeof(long), 1, file) <= 0) {
        #ifdef VERBOSE_MODE
        HANDLE_ERROR("Error reading last register");
        #endif // VERBOSE_MODE
    }
}

void recordFirstRecord() {
    resetFileIndicator();
    if(fwrite(&firstReg, sizeof(long), 1, file) <= 0) {
        HANDLE_ERROR("Error writing first register");
    }
}

void recordLastRecord() {
    setFileIndicator(sizeof(long));

    if(fwrite(&lastReg, sizeof(long), 1, file) <= 0) {
        HANDLE_ERROR("Error writing last register");
    }
}

int deleteFile(char *name) {
    return remove(name);
}
