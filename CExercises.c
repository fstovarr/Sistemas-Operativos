#include "stdio.h"
#include <stdlib.h>

struct dataType{
    char n[3];
    int edad;
};

int main() {
    int m[] = {0,1,2,3,4,5,6,7,8,9,10};
    printf("%d | %d", m[0], *(m + 10));

    struct dataType *d;
    d = (struct dataType*) malloc(sizeof(struct dataType));
    d -> edad = 11010100;

    char arr[] = {'a','b','c'};

    for(int i = 0; i < 3; i++) {
        *((d -> n) + i) = *(arr + i);
    }

    for(int i = 0; i < 3; i++)
        printf("\n-> %c ", *((d->n) + i));

    printf("\n\n%d",'1');
}
