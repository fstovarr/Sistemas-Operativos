#include <stdio.h>
#include <stdbool.h>

#define HANDLE_ERROR(arg) perror(arg)
#define FOLDER_NAME "medicalrecords/"

extern long firstReg;
extern long lastReg;

struct DogType *dummyPet;

void buildName(char* nm, int res, char* ans);
char* subString (const char* input, int offset, int len, char* dest);

void initProcess();

void enterRecord();
void showRecord();
void deleteRecord();
void searchRecord();
void closeProgram();
void printTable();

void notifyRecordFound(struct DogType *pet);
void notifySearchFinished();

void setFirstRecord(long first);
void setLastRecord(long last);

long calcRecordNumber();
