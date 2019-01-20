#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

<<<<<<< HEAD
#define HASH_SIZE 99566893
#define MAGIC_PRIME 99566879
//#define HASH_SIZE 17
//#define MAGIC_PRIME 13
#define NUMBER_PETS 10000000

#define FILE_NAME "dataDogs.dat"
#define FOLDER_NAME "medicalrecords/"

#define HANDLE_ERROR(msg) perror(msg);

=======
//#define HASH_SIZE 9999889
//#define MAGIC_PRIME 9999667
#define HASH_SIZE 17
#define MAGIC_PRIME 13

#define FILE_NAME "dataDogs.dat"
#define FOLDER_NAME "/medicalrecords/"

#define HANDLE_ERROR(msg) perror(msg);

typedef enum { false, true } bool;

>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
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

void printDogType(struct DogType* dogType) {
    printf("Name: %s\n", dogType->name);
    printf("Type: %s\n", dogType->type);
    printf("Age: %d\n", dogType->age);
    printf("Race: %s\n", dogType->race);
    printf("Height: %d\n", dogType->height);
    printf("Weight: %.2f\n", dogType->weight);
}

/**
 * Add a element in the hash table with collisions handler
 * @param DogType* dogType pointer of the element with all data of pet
 */
void addInHash(struct DogType* dogType, bool addReg, int reg) {
    unsigned long position = hash(dogType->name);
    unsigned long step = hash2(position) * 32;
    int i = 0;
    unsigned long finalPosition = 0;

    do {
        finalPosition = (position % HASH_SIZE + (i++ * step) % HASH_SIZE) % HASH_SIZE;
        //printf("%d - %d\n", finalPosition, table[finalPosition]);
    } while(table[finalPosition] != 0);

    struct Item* newItem;
    newItem = (struct Item*) calloc(1, sizeof(struct Item));
    mempcpy(newItem->key, dogType->name, 32);
    mempcpy(&newItem->value, dogType, sizeof(struct DogType*));

<<<<<<< HEAD
    if(addReg) {
        mempcpy(&newItem->regNumber, &regIndex, sizeof(long long));
    } else {
        newItem->regNumber = reg;
    }
=======
    registers[regIndex++] = *dogType;
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34

    table[finalPosition] = newItem;

<<<<<<< HEAD
    if(addReg){
        mempcpy(&registers[regIndex], dogType, sizeof(struct DogType));
        regIndex++;
    }

    hashSize++;
=======
    free(newItem);

    saveState();
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
}

/**
 * Remove a element identified with a @param name and a @param regNumber
 */
void removeInHash(char name[32], int regNumber) {
    unsigned long position = hash(name);
    unsigned long step = hash2(position) * 32;
    int i = 0;
    unsigned long finalPosition = 0;

    do {
        finalPosition = (position % HASH_SIZE + i++ * step) % HASH_SIZE;
    } while(table[finalPosition] != 0 && table[finalPosition]->regNumber != regNumber);

    memset(&registers[regNumber], 0, sizeof(struct DogType));
    memset(&table[finalPosition], 0, sizeof(struct Item));

<<<<<<< HEAD
=======
    registers[regNumber] = deleted;
    table[finalPosition] = 0;
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    hashSize--;

    saveState();
}

/**
 * Search in the hash table for the register numbers
 */
void searchInHash(char* name) {
    unsigned long position = hash(name);
    unsigned long step = hash2(position) * 32;
    unsigned long finalPosition = position % HASH_SIZE;
    int i = 0;

    //printf("%s %d %d %d", name, position%HASH_SIZE, step, finalPosition);
<<<<<<< HEAD
    printf("REGISTER\tNAME\n----------------------------------------------------------\n");
    finalPosition = (position % HASH_SIZE);

    while(table[finalPosition] != 0) {
        char *n1 = table[finalPosition]->key;
        int res = strcasecmp(n1, name);
        //printf("\n%d - %s - %s\n", res, n1, name);

        if(res == 0) {
            //printf("%d\n", table[finalPosition]->key);
            long long tmp = table[finalPosition]->regNumber;
            printf("%lld\t\t%s\n", tmp + 1, name);
        }
        finalPosition = (position % HASH_SIZE + ++i * step) % HASH_SIZE;
    }
=======

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
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
}

void printTable(){
    for(int i = 1; i < HASH_SIZE; i++) {
        long long tmp = (long long) &table[i]->regNumber;
        if(tmp > 32)
            tmp = *(&table[i]->regNumber);
        printf("%d %d -> %lld %s\n", i, table[i], tmp, table[i]->key);
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

<<<<<<< HEAD
	addInHash(p, true, 0);
=======
	addInHash(p);
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
}

void showRecord() {
    printf("%d registros existentes\nIngrese el número del registro que desea ver: ", hashSize);
    int rec;
    scanf("%d", &rec);
    rec--;
    int res = 0;

<<<<<<< HEAD
    if(&registers[rec] != 0) {
        char *name = (char*) malloc(100);
        buildName(&registers[rec].name, rec+1, name);
        openFile(name);
=======
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
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    } else {
        printf("El registro %d no existe", rec + 1);
    }
}

void deleteRecord() {
    printf("%d registros existentes\nIngrese el número del registro que desea eliminar: ", hashSize);
    int rec;
    scanf("%d", &rec);
    int res = 0;
    rec--;

<<<<<<< HEAD
    if(hashSize > 0 && rec >= 0 && rec <= regIndex) {
        char *name = (char*) malloc(100);
        buildName(&registers[rec].name, rec, name);
        deleteFile(name);
        removeInHash(registers[rec].name, rec);
        printf("El registro fue eliminado exitosamente");
=======
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
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    } else {
        printf("El registro %d no existe", rec + 1);
    }
}

void closeprogram() {
    exit(0);
}

<<<<<<< HEAD
void buildName(char* nm, int res, char* ans) {
    strcpy(ans, FOLDER_NAME);
    char it[12];
    sprintf(it, "%d", res);
    strcat(ans, &it);
    strcat(ans, nm);
    strcat(ans, ".txt");
}

int openFile(char* name) {
    printf("%s", name);
    char command[30];
    strcpy(&command, "gedit ");
    strcat(&command, name);
    system(command);
    return 1;
}

int deleteFile(char *name) {
    return remove(name);
}

void printReg(int n) {
    for(int i = 0; i < n; i++) {
            //printf("%s", registers[i].name);
        printf("%d\t | %s - %d\n", i, registers[i].name, registers[i].age);
=======
void printReg() {
    for(int i = 0; i < regIndex; i++) {
        printf("%d\t%s - %d\n", i, registers[i].name, registers[i].age);
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    }
}

/**
 * Load the data saved in some points of process execution
 */
void loadState() {
<<<<<<< HEAD
=======
    initMemory();

>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    FILE *f;
    f = fopen(FILE_NAME, "rb+");
    if(f == NULL) {
        //HANDLE_ERROR("Error abriendo el archivo de persistencia");
        return;
    }

    int r = fread(&regIndex, sizeof(long long), 1, f);
    if(r <= 0){
<<<<<<< HEAD
        HANDLE_ERROR("Error leyendo el número de registros");
        return;
    }

=======
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

>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
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

<<<<<<< HEAD
    syncHashWithRegisters();
    printf("Se han cargado exitosamente todos los registros");
=======
    printf("Se ha cargado su registro exitosamente");
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
}

/**
 * Handle the data persistence in system
 */
void saveState() {
<<<<<<< HEAD
    FILE *f;
=======
    /*FILE *f;
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    f = fopen(FILE_NAME, "wb+");

    if(f == NULL) {
        HANDLE_ERROR("Error abriendo el archivo de persistencia");
        return;
    }

<<<<<<< HEAD
    if(hashSize == 0)
        return;

=======
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    // Save the struct size for read
    int r = fwrite(&regIndex, sizeof(long long), 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error guardando el numero de registros");
        return;
    }

<<<<<<< HEAD
=======
    r = fwrite(&hashSize, sizeof(int), 1, f);
    if(r <= 0){
        HANDLE_ERROR("Error guardando el tamaño de la tabla");
        return;
    }

>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
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

<<<<<<< HEAD
    //printf("%d %d\n", regIndex, hashSize);
    printf("Se ha guardado su registro exitosamente\n");
}

void syncHashWithRegisters() {
    printf("Cargando registros...\n");
    int counter = regIndex;
    for(int i = 0; i < regIndex; i++) {
        printf("%.2f %\r", ((i*1.0)/(counter*1.0)) * 100);
        addInHash(&registers[i], false, i);
    }
    printf("%.2f %\n", 100.0);
}

char* subString (const char* input, int offset, int len, char* dest) {
  int input_len = strlen (input);

  if (offset + len > input_len) {
     return NULL;
  }

  strncpy (dest, input + offset, len);
  return dest;
}

void loadPetsFromFile(int pets) {
    FILE *f;
    f = fopen("names.txt","r");
    if(f == NULL)
        HANDLE_ERROR("Error al cargar nombres")

    char *names = (char*) calloc(1005, 32);
    char *buffer = NULL;
    int c = 0;
    size_t len = 0, read;

    struct DogType *p;

    while ((read = getline(&buffer, &len, f)) != -1) {
        subString (buffer, 0, read - 2, names + 32*c);
        toLower(names + 32 * c++);
    }

    p = (struct DogType*) malloc(sizeof(struct DogType));

    printf("Cargando %d mascotas...\n", pets);

    srand(time(NULL));   // Seed init, should only be called once.
    for(int i = 0; i < pets; i++) {
        printf("%.2f %\r", ((i*1.0)/(pets*1.0)) * 100);

        int r = rand() % 1000;
        //printf("%d\n", r);

        strncpy (p->name, names + 32 * r, 32);
        mempcpy(p->type, "Perro", 32);
        p->age = 10;
        mempcpy(p->race, "Chihuahua", 32);
        p->height = 666;
        p->weight = 20.5;

        char tmp = 'm';
        mempcpy((&p->sex), &tmp, sizeof(char));

        addInHash(p, true, 0);
    }

    printf("%.2f %\n", 100.0);

    fclose(f);
    free(buffer);
    free(names);
    free(p);
=======
    printf("Se ha guardado su registro exitosamente");*/
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
}

void searchRecords() {
    printf("Digite el nombre que desea buscar: ");
    char nm[32];
    scanf("%s", &nm);
<<<<<<< HEAD
=======
    printf("%s", nm);
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
    searchInHash(nm);
}

int main() {
    initMemory();
    loadState();
<<<<<<< HEAD
    wait();
    //loadPetsFromFile(NUMBER_PETS);
    system("clear");
    wait();

    saveState();

	while(true) {
		int opc = 0;
		while(opc != 5) {
            printf("1. Ingresar registro\n2. Ver registro\n3. Borrar registro\n4. Buscar registro\n5. Salir\n");
            scanf("%i", &opc);
            wait();
            int limit = regIndex;
            //int limit = 20;
            switch(opc){
                case 1:
                    record();
                    saveState();
                    break;
                case 2:
                    showRecord();
                    break;
                case 3:
                    deleteRecord();
                    saveState();
                    break;
                case 4:
                    searchRecords();
                    break;
                case 5:
                    closeprogram();
                    break;
                case 6:
                    printTable();
                    break;
                case 7:
                    printReg(limit);
                    break;
                default:
                    HANDLE_ERROR("Código erróneo");
                    break;
            }
            wait();
            system("clear");
=======

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
>>>>>>> bda18777af50bf56b3e3a42202af1bbe29169c34
		}
	}
}
