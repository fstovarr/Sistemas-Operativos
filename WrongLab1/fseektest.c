#include <stdio.h>

struct Test{
    int test;
    int test2;
};

int main() {
    struct Test* t1 = malloc(sizeof(struct Test));
    struct Test* t2 = malloc(sizeof(struct Test));
    struct Test* t3 = malloc(sizeof(struct Test));

    t1->test = 2;
    t1->test2 = 3;
    t2->test = 4;
    t2->test2 = 5;
    t3->test = 6;
    t3->test2 = 7;

    printf("%d - %d - %d\n", t1->test, t2->test, t3->test);

    FILE *f;
    f = fopen("test.txt", "w+");

    fwrite(t1, sizeof(struct Test), 1, f);
    fwrite(t2, sizeof(struct Test), 1, f);
    fwrite(t3, sizeof(struct Test), 1, f);

    fclose(f);

    f = fopen("test.txt", "r");
    fread(t1, sizeof(struct Test), 1, f);

    fseek(f, sizeof(struct Test), SEEK_CUR);
    fread(t2, sizeof(struct Test), 1, f);

    fseek(f, sizeof(struct Test), SEEK_SET);
    fread(t3, sizeof(struct Test), 1, f);

    printf("%d - %d - %d", t1->test, t2->test, t3->test);
    fclose(f);

}
