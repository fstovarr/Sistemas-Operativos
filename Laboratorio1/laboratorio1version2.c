#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "HashTable.h"
#include "Laboratorio1.h"

void initProcess() {
    initHashTable();
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
	char tmp = getSex(0);
	mempcpy((&p->sex), &tmp, sizeof(char));

	insert(p);
}

void showRecord() {
}

void deleteRecord() {
}

void searchRecord() {
    printf("Digite el nombre que desea buscar: ");
    char nm[32];
    scanf("%31s", nm);
}

void closeprogram() {
    exit(0);
}

void printTable() {
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

char getSex(char p) {
	if (p=='H'||p=='h' || p == 'M' || p=='m'){
		return p;
	}else{
		printf("Por favor introduzca H (Hembra)o M (Macho)\n" );
		scanf("%s",&p);
        return getSex(p);
	}
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
                    printTable();
                    break;
                case 7:
                    //printReg(limit);
                    break;
                default:
                    //HANDLE_ERROR("Código erróneo");
                    break;
            }
            wait();
            system("clear");
		}
	}
}
