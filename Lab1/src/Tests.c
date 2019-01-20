#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Tests.h"
#include "Laboratorio1.h"
#include "HashTable.h"

void fillWithRandomAnimals() {
    namesFile = fopen("names.txt", "r");
    char* words[1005][20];
    char* line = NULL;
    size_t len = 0;
    int wordCounter = 0;

    if(namesFile != NULL) {
        while((len = getline(&line, &len, namesFile)) != EOF) {
            mempcpy(words[wordCounter++], line, len - 2);
        }
    } else {
        HANDLE_ERROR("Error reading the file.");
    }

    free(line);

    struct DogType *p = (struct DogType*) malloc(sizeof(struct DogType));
    //char n[32];

    printf("Loading test animals\n");

    int n = 0;
    for(int i = 0; i < ANIMALS; i++) {
        n = random() % wordCounter;
        toLower(words[n]);
        mempcpy(p->name, words[n], 20);
        mempcpy(p->type, "Perrito", 7);
        p->age = 1 + random() % 32;
        mempcpy(p->race, "Beagle", 6);
        p->height = 50 + random() % 50;
        p->weight = 20 + random() % 10;
        char tmp = ((random() % 2) == 0) ? true : false;
        mempcpy((&p->sex), &tmp, sizeof(char));
        insert(p);
        if(i % 5 == 0)
            printf("\r%.2f %", (i * 100.0 / ANIMALS));
    }

    free(p);
}
