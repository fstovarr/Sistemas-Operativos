#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "Laboratorio1.h"
#include "HashTable.h"
#include "FileManager.h"
#include "Tests.h"

long firstReg = -1;
long lastReg = -1;

void initProcess() {
    bool firstTime = initFile();
    loadFirstRecord();
    loadLastRecord();
    //printf("First? %d\n", firstTime);
    initHashTable(firstTime);

    if(firstTime) {
        fillWithRandomAnimals();
    }
}

/**
 * Función donde se solicitan datos y almacenan
 */
void enterRecord() {
    //Reserva espacio para estructura
	struct DogType *p = (struct DogType*) malloc(sizeof(struct DogType));

	char n[32];
	printf("Nombre: ");
	scanf("%s", n);
	toLower(n);
    mempcpy(p->name, &n, sizeof(n));
	printf("Tipo: ");
	scanf("%s", p->type);
	printf("Edad: ");
	scanf("%i", &p->age);
	printf("Raza: ");
	scanf("%s", p->race);
	printf("Estatura: ");
	scanf("%i", &p->height);
	printf("Peso: ");
	scanf("%lf", &p->weight);
	printf("Sexo: ");
	p->sex = getSex(0);

	insert(p);
}

void showRecord() {
    printf("Ingrese el número del registro que desea ver: ");
    int rec;
    scanf("%d", &rec);
    rec--;

    struct Node* node = (struct Node*) calloc(1, sizeof(struct Node));
    char *name = (char*) malloc(100);

    if(getNodeByEntryOrder(node, rec) == true && node->key != -1) {
        buildName(node->data.name, rec + 1, name);
        openFile(name);
    } else {
        printf("El registro %d no existe", rec + 1);
    }

    free(node);
    free(name);
}

void deleteRecord() {
    printf("Ingrese el número del registro que desea eliminar: ");

    int rec;
    scanf("%d", &rec);
    rec--;

    struct Node* node = (struct Node*) calloc(1, sizeof(struct Node));
    char *name = (char*) malloc(100);

    if(getNodeByEntryOrder(node, rec) == true && node->key != -1) {
        buildName(node->data.name, rec + 1, name);
        deleteFile(name);
        removeItem(node);
        //printf("%s\n", name);
        printf("El registro fue eliminado exitosamente");
    } else {
        printf("El registro %d no existe", rec + 1);
    }

    free(node);
    free(name);
}

void searchRecord() {
    printf("Digite el nombre que desea buscar: ");
    char nm[32];
    scanf("%31s", nm);
    search(nm);
}

void closeprogram() {
    closeFile();
    exit(0);
}

/**
 * Función que permite pausar la operación actual hasta que el
 * usuario lo desee.
 */
void wait(){
	printf("\nPara continuar, presione la tecla ENTER");
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

bool getSex(char p) {
	if (p=='H'||p=='h' || p == 'M' || p=='m'){
		return (p == 'H' || p == 'h') ? true : false;
	}else{
		printf("Por favor introduzca H (Hembra)o M (Macho)\n" );
		scanf("%s",&p);
        return getSex(p);
	}
}

int openFile(char* name) {
    printf("%s", name);
    char command[30];
    strcpy(command, "gedit ");
    strcat(command, name);
    system(command);
    return 1;
}

int deleteFile(char *name) {
    return remove(name);
}

void buildName(char* nm, int res, char* ans) {
    strcpy(ans, FOLDER_NAME);
    char it[12];
    sprintf(it, "%d", res);
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

int main() {
    initProcess();
    wait();

	while(true) {
		int opc = 0;
		while(opc != 5) {
            printf("1. Ingresar registro\n2. Ver registro\n3. Borrar registro\n4. Buscar registro\n5. Salir\n");
            scanf("%i", &opc);
            wait();
            //int limit = 20;
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
                    closeprogram();
                    break;
                case 6:
                    //printTable();
                    break;
                case 7:
                    printf("First register: %ld - Second register: %ld\n", firstReg, lastReg);
                    printFirstNodes(5);
                    break;
                default:
                    HANDLE_ERROR("Código erróneo");
                    break;
            }
            wait();
            system("clear");
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
