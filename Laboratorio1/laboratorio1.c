#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//#define HASH_SIZE 9999889
//#define MAGIC_PRIME 9999667
#define HASH_SIZE 17
#define MAGIC_PRIME 13

#define FILE_NAME "dataDogs.dat"
#define FOLDER_NAME "/medicalrecords/"

#define HANDLE_ERROR(msg) perror(msg);

typedef enum { false, true } bool;

struct DogType {
    char name[32];
    char type[32];
    int age;
    char race[16];
    int height;
    double weight;
    bool sex;
};

struct Item {
    char key[32];
    long long regNumber;
    struct DogType* value;
};

struct DogType* registers;
struct Item* table[HASH_SIZE];
bool memTable = false;
long long regIndex = 0;
int hashSize = 0;

/**
 * DJB2 hash function over @param str char array
 */
unsigned long hash(unsigned char *str) {
    toLower(str);
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/**
 * Helper hash function to collision solution
 */
unsigned long hash2(unsigned long key) {
    return MAGIC_PRIME - (key % MAGIC_PRIME);
}

/**
 * Initialize the Hash Table and the Registers with size @param HASH_SIZE
 */
void initMemory() {
    if(!memTable) {
        *table = (struct Item*) calloc(HASH_SIZE, sizeof(struct Item));
        registers = calloc(HASH_SIZE, sizeof(struct DogType));
        memTable = true;
    }
    //*table = (struct Item*) malloc(sizeof(struct Item) * HASH_SIZE);
    //memset(*table, -1, sizeof(table));
}

/**
 * Add a element in the hash table with collisions handler
 * @param DogType* dogType pointer of the element with all data of pet
 */
void addInHash(struct DogType* dogType) {
    unsigned long position = hash(dogType->name);
    unsigned long step = hash2(position);
    int i = 0;
    unsigned long finalPosition = 0;

    do {
        finalPosition = (position % HASH_SIZE + i++ * step) % HASH_SIZE;
    } while(table[finalPosition]->key != 0);

    struct Item* newItem;
    newItem = (struct Item*) calloc(1, sizeof(struct Item));
    mempcpy(newItem->key, dogType->name, 32);

    mempcpy(&newItem->value, dogType, sizeof(struct DogType*));
    mempcpy(&newItem->regNumber, &regIndex, sizeof(int));

    registers[regIndex++] = *dogType;

    table[finalPosition] = newItem;
    hashSize++;

    free(newItem);

    saveState();
}

/**
 * Remove a element identified with a @param name and a @param regNumber
 */
void removeInHash(char name[32], int regNumber) {
    unsigned long position = hash(name);
    unsigned long step = hash2(position);
    int i = 0;
    unsigned long finalPosition = 0;

    do {
        finalPosition = (position % HASH_SIZE + i++ * step) % HASH_SIZE;
    } while(table[finalPosition] == 0 && regNumber != table[finalPosition]->regNumber);

    struct DogType deleted;
    mempcpy(deleted.type, "-1", 1);
    mempcpy(deleted.name, "-1", 1);

    registers[regNumber] = deleted;
    table[finalPosition] = 0;
    hashSize--;

    saveState();
}

/**
 * Search in the hash table for the register numbers
 */
void searchInHash(char* name) {
    unsigned long position = hash(name);
    unsigned long step = hash2(position);
    int i = 0;
    unsigned long finalPosition = 0;

    //printf("%s %d %d %d", name, position%HASH_SIZE, step, finalPosition);

    do {
        finalPosition = (position % HASH_SIZE + i++ * step) % HASH_SIZE;
        const char* n1 = table[finalPosition]->key;

        if(strcmp(&n1, &name)) {
            //printf("YEEEs", n1);
            printf("%s - %s\n", n1, name);
            long long tmp = table[finalPosition]->regNumber;
            printf("%lld - %s\n", tmp, name);
        }
    } while(table[finalPosition] != 0);
}

void printTable(){
    for(int i = 1; i < HASH_SIZE; i++) {
        long long tmp = (long long) &table[i]->regNumber;
        if(tmp > 32)
            tmp = *(&table[i]->regNumber);
        printf("%d %d -> %lld %s\n", i, table[i], tmp, *(&table[i]->key));
    }
}

/**
 * Función que espera enter
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

void toLower(char *str) {
    for(; *str; ++str) *str = tolower(*str);
}

/**
 * Función donde se solicitan datos y almacenan
 */
void record(){
	struct DogType *p =(struct DogType*) malloc(sizeof(struct DogType));//Reserva espacio para estructura
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
	scanf("%f", &p->weight);
	printf("Sexo: ");
	char tmp = getSex(0);
	mempcpy((&p->sex), &tmp, sizeof(char));

	addInHash(p);
}

void showRecord() {
    printf("%d registros existentes\nIngrese el número del registro que desea ver: ", hashSize);
    int rec;
    scanf("%d", &rec);
    rec--;

    int res = 0;

    printf("%s",registers[rec].name);

    if(&registers[rec] != 0) {
        FILE *file;
        char fName[200];
        strcpy(&fName, "medicalrecords/");

        char it[12];
        sprintf(it, "%d", res);
        strcat(&fName, &it);

        printf("Name: %s, Record: %d\n", registers[rec].name, rec);
        strcat(&fName, registers[rec].name);
        strcat(&fName, ".txt");
        res = fopen(&fName, "a+");
        if(res<-1)
            HANDLE_ERROR("Error al abrir el archivo de la historia clinica")

        char command[30];
        strcpy(&command, "gedit ");
        strcat(&command, &fName);
        system(command);
    } else {
        printf("El registro %d no existe", rec + 1);
    }
}

void deleteRecord() {
    printf("%d registros existentes\nIngrese el número del registro que desea eliminar: ", hashSize);
    int rec;
    scanf("%d", &rec);
    rec--;
    int res = 0;

    //printf(registers[rec]->type);
    if(&registers[rec] != 0) {
        FILE *file;
        char fName[200];
        strcpy(&fName, FOLDER_NAME);

        char it[12];
        sprintf(it, "%d", res);
        strcat(&fName, &it);

        //printf("Name: %s, Record: %d\n", registers[rec]->name, rec);
        strcat(&fName, registers[rec].name);
        strcat(&fName, ".txt");
        res = fopen(&fName, "a+");
        if(res<-1)
            HANDLE_ERROR("Error al abrir el archivo de la historia clinica")

        char command[30];
        strcpy(&command, "gedit ");
        strcat(&command, &fName);
        system(command);
    } else {
        printf("El registro %d no existe", rec + 1);
    }
}

void closeprogram() {
    exit(0);
}

void printReg() {
    for(int i = 0; i < regIndex; i++) {
        printf("%d\t%s - %d\n", i, registers[i].name, registers[i].age);
    }
}

/**
 * Load the data saved in some points of process execution
 */
void loadState() {
    initMemory();

    FILE *f;
    f = fopen(FILE_NAME, "rb+");
    if(f == NULL) {
        //HANDLE_ERROR("Error abriendo el archivo de persistencia");
        return;
    }

    int r = fread(&regIndex, sizeof(long long), 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error leyendo el número de registro");
        return;
    }

    r = fread(&hashSize, sizeof(int), 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error leyendo el tamaño de la tabla hash");
        return;
    }

    /*
    r = fread(table, sizeof(struct Item) * HASH_SIZE, 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error leyendo el tamaño de la estructura");
        return;
    }*/

    r = fread(registers, sizeof(struct DogType) * regIndex, 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error leyendo los registros");
        return;
    }

    r = fclose(f);
    if(r == EOF){
        HANDLE_ERROR("Error cerrando el archivo");
        return;
    }

    printf("Se ha cargado su registro exitosamente");
}

/**
 * Handle the data persistence in system
 */
void saveState() {
    /*FILE *f;
    f = fopen(FILE_NAME, "wb+");

    if(f == NULL) {
        HANDLE_ERROR("Error abriendo el archivo de persistencia");
        return;
    }

    // Save the struct size for read
    int r = fwrite(&regIndex, sizeof(long long), 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error guardando el numero de registros");
        return;
    }

    r = fwrite(&hashSize, sizeof(int), 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error guardando el tamaño de la tabla");
        return;
    }

    r = fwrite(registers, sizeof(struct DogType) * regIndex, 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error guardando los registros");
        return;
    }

    r = fclose(f);
    if(r == EOF){
        HANDLE_ERROR("Error cerrando el archivo");
        return;
    }

    printf("Se ha guardado su registro exitosamente");*/
}

void searchRecords() {
    printf("Digite el nombre que desea buscar: ");
    char nm[32];
    scanf("%s", &nm);
    printf("%s", nm);
    searchInHash(nm);
}

int main() {
    initMemory();
    loadState();

	while(true) {
		int opc;
		printf("\n1. Ingresar registro\n2. Ver registro\n3. Borrar registro\n4. Buscar registro\n5. Salir\n");
		scanf("%i", &opc);

		if(opc==1){
			wait();
			record();
			wait();
		}else if(opc == 2){
			wait();
			showRecord();
			wait();
		}else if(opc == 3){
			wait();

			wait();
		}else if(opc == 4){
		    printTable();
		    printReg();
		    wait();
		    searchRecords();
			wait();
		}else if (opc == 5){
			closeprogram();
		}
	}
}
