#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#include "main.h"
#include "ClientController.h"

int main() {
    p = (struct DogType*) malloc(sizeof(struct DogType));
    requestConnection();
    while(true)
        showMenu();
}

void enterRecord() {
    char n[32];
    printf("Name: ");
    scanf("%s", n);
    //toLower(n);
    mempcpy(p->name, &n, sizeof(n));
    printf("Type: ");
    scanf("%s", p->type);
    printf("Age: ");
    scanf("%i", &p->age);
    printf("Race: ");
    scanf("%s", p->race);
    printf("Height: ");
    scanf("%i", &p->height);
    printf("Weight: ");
    scanf("%lf", &p->weight);
    printf("Sex: ");
    p->sex = getSex(0);

    sendMessage(p, sizeof(struct DogType));
}

void showRecord() {
    printf("Enter the number of record you want to see: ");
    int rec;
    scanf("%d", &rec);
    rec--;
    sendMessage(&rec, sizeof(int));

    int ans;
    receiveMessage(&ans, sizeof(int));
    if(ans != -1) {
        char *name = receiveFile();
        openFile(name);
        sendFileUpdated(name, 100);
        deleteFile(name);
    } else {
        printf("Record %d does not exists.", rec + 1);
    }
}

void deleteRecord() {
    printf("Enter the number of record you want to delete: ");

    int rec;
    scanf("%d", &rec);
    rec--;
    sendMessage(&rec, sizeof(int));
    receiveMessage(&rec, sizeof(int));

    if(rec == -1) {
        printf("Record does not exists.\n");
    } else {
        printf("Deleting record successfully.\n");
    }
}

void printDogType(struct DogType* dogType) {
    printf("Name: %s\n", dogType->name);
    printf("Sex: %c\n", (dogType->sex == 1) ? 'M' : 'F');
    printf("Type: %s\n", dogType->type);
    printf("Age: %d\n", dogType->age);
    printf("Race: %s\n", dogType->race);
    printf("Height: %d\n", dogType->height);
    printf("Weight: %.2f\n", dogType->weight);
}

void searchRecord() {
    printf("Name to search: ");
    char nm[32];
    scanf("%31s", nm);
    sendMessage(nm, sizeof(nm));

    for(;;) {
        receiveMessage(p, sizeof(struct DogType));
        if(p->age == -1) break;
        printDogType(p);
        printf("----------------------\n");
    }
}

void closeProgram() {
    close(socketClient);
    exit(0);
}

void showMenu() {
    int opc = 0;
    while(opc != 5) {
        printf("1. Enter record\n2. Show record\n3. Delete record\n4. Search record\n5. Exit\n");
        scanf("%i", &opc);
        sendMessage(&opc, sizeof(opc));

        switch(opc){
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
                closeProgram();
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                HANDLE_ERROR("Not valid option.");
                break;
        }

        wait();
    }
}

int openFile(char* name) {
    #ifdef VERBOSE_MODE
    printf("%s", name);
    #endif // VERBOSE_MODE
    char command[30];
    strcpy(command, "gedit ");
    strcat(command, name);
    system(command);
    return 1;
}

int deleteFile(char *name) {
    return remove(name);
}

bool getSex(char p) {
    if (p=='H'||p=='h' || p == 'M' || p=='m'){
        return (p == 'H' || p == 'h') ? true : false;
    }else{
        printf("Please write H to Female or M to Male\n" );
        scanf("%s",&p);
        return getSex(p);
    }
}

void wait(){
    printf("\nPress ENTER to continue...\n");
    char prev = 0;
    while(1){
        char c = getchar();
        if(c =='\n' && prev == c){
            break;
        }
        prev = c;
    }
    system("clear");
}
