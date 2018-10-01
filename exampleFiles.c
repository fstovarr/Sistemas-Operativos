#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dataType
{
    char n[30];
    int edad;
    char genero;
    float estatura;
};

void loadStruct(void *m, char *w, int e, int n)
{
    struct dataType *a = m;
    //memset(&(a->edad), 0, sizeof(int));
    a -> edad = 0;
    mempcpy(a->n, w, n);
    a -> edad = (int) e;
}

void loadStruct2(void *m) {
    struct dataType *a = m;
    scanf("%s ", a->n);
    scanf("%d", &(a->edad));
}

int main()
{
    FILE *f;
    int r;
    struct dataType *persona;
    persona = (struct dataType*) malloc(sizeof(struct dataType));

    if(persona == NULL)
    {
        perror("Error en malloc");
        exit(-1);
    }

    memset(persona->n, ' ', sizeof(struct dataType) - sizeof(int));

    //loadStruct(persona, "Fabio Tovar", 100, 11);
    loadStruct2(persona);

    f = fopen("data.dat", "w+");

    if(f == NULL) {
        perror("Error fopen");
        exit(-1);
    }

    r = fwrite(persona, sizeof(struct dataType), 1, f);

    if(r == 0) {
        perror("Error fwrite");
        exit(-1);
    }

    r = fclose(f);

    if(r!=0) {
        perror("Error fclose");
        exit(-1);
    }

    free(persona);
}
