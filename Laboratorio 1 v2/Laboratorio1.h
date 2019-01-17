#include <stdbool.h>

#define NUMBER_PETS 10000000
#define HANDLE_ERROR(arg) perror(arg)
#define FOLDER_NAME "medicalrecords/"

extern long firstReg;
extern long lastReg;

void wait();
bool getSex(char p);
void buildName(char* nm, int res, char* ans);
char* subString (const char* input, int offset, int len, char* dest);

int openFile(char* name);
int deleteFile(char* name);

void initProcess();

void enterRecord();
void showRecord();
void deleteRecord();
void searchRecord();
void closeprogram();
void printTable();

void setFirstRecord(long first);
void setLastRecord(long last);

long calcRecordNumber();
