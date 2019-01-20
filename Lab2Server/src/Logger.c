#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>

#include "main.h"
#include "Logger.h"

//#define VERBOSE_MODE

void initLogger() {
    dummyLog = malloc(sizeof(struct Log));

    if((logger = fopen(LOGGER_FILE_NAME, "ab+")) == NULL) {
        HANDLE_ERROR("Error trying to open log file");
        return;
    }

    setbuf(logger, NULL);
}

void registerIntOperation(char *ip, short operation, int input) {
    bzero(tmp, sizeof(tmp));
    snprintf(tmp, sizeof(tmp), "%d", input);
    registerOperation(ip, operation, tmp, sizeof(int));
}

void registerOperation(char *ip, short operation, char *input, size_t sizeInput) {
    bzero(dummyLog, sizeof(dummyLog));

    t = time(NULL);
    tim = localtime(&t);

    if(strftime(dummyLog->date, sizeof(dummyLog->date), "%Y%m%d%H%M%S", tim) <= 0) {
        //HANDLE_ERROR("Possible error");
    }

    mempcpy(dummyLog->ip, ip, sizeof(dummyLog->ip));
    dummyLog->operation = operation;
    mempcpy(dummyLog->input, input, sizeInput);

    if((result = fwrite(&dummyLog, sizeof(struct Log), 1, logger)) <= 0) {
        HANDLE_ERROR("Error writing in file");
        return;
    } else {
	#ifdef VERBOSE_MODE
        printf("File written %lu\n", result);
	#endif
    }

    #ifdef VERBOSE_MODE
    printLog(dummyLog);
    printf("\n");
    #endif // VERBOSE_MODE
}

void printLog(struct Log *log) {
    printf("Date: %s | Client %s | Operation %hi | Input: %s", log->date, log->ip, log->operation, log->input);
}
