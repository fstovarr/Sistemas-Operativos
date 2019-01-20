#include <stdbool.h>
#include <stdio.h>

#define HANDLE_ERROR(arg) perror(arg);

struct DogType {
    char name[32];
    char type[32];
    int age;
    char race[16];
    int height;
    double weight;
    bool sex;
};

struct DogType *p;

void wait();
void closeProgram();

bool getSex(char p);
void showMenu();
int openFile(char* name);
int deleteFile(char* name);
void printDogType(struct DogType *pet);

void enterRecord();
void showRecord();
void deleteRecord();
void searchRecord();
void closeprogram();
void printTable();
