#include <stdbool.h>
//#define HASH_SIZE 6000011
#define HASH_SIZE 17
//#define MAGIC_PRIME 13

struct DogType {
    char name[32];
    char type[32];
    int age;
    char race[16];
    int height;
    double weight;
    bool sex;
};

struct Node {
    int key;
    struct DogType data;
    long nextHashItem;
    long position;
};

struct HashItem {
    long head;
};

struct HashItem* hashArray;
struct HashItem* dummyItem;

extern long previousItem;

struct Node* prevDummyNode;
struct Node* dummyNode;
struct Node* lastNode;

extern bool booleanBuffer;

void initHashTable(bool first);
unsigned long hash(char *str);
void insert(struct DogType *dogType);
void search(char* key);
void removeItem(struct Node* node);

void toLower(char* str);
void printDogType(struct DogType* dogType);
void printTable();
void printFirstNodes(long quantity);
