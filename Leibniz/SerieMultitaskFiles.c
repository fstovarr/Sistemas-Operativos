#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

double calc(int start, int end, int parent) {
    double res = 0;
    int counter = 0;

    for(double i = start; i < end; i+=2) {
        double d = (4.0 / i);

        if(counter++ % 2 == 0) {
            res = res + d;
        } else {
            res = res - d;
        }
    }

    if(parent == 1) {
       FILE *f;

        do {
            f = fopen("child.out", "r");
        } while(f == NULL);

        double *c;
        fread(c, sizeof(double), 1, f);
        fclose(f);

        res += *c;
        printf("Parent finish.\n");
        printf("Result %.15f\n", res);
        //remove("child.out");
    } else {
        FILE *f;
        f = fopen("child.out", "w+");
        fwrite(&res, sizeof(double), 1, f);
        //fclose(f);
        printf("Child finish.\n");
    }
}


int main() {
	pid_t pid;
	pid = fork();

	if(pid < 0) {
		perror("ERROR :(");
		exit(-1);
	} else if (pid == 0) {
		printf("[%d] Child started...\n", getpid());
		calc(1, 500e6 * 2, 0);
	} else {
		printf("[%d] Parent started...\n", getpid());
		calc(500e6 * 2 + 1, 1e9 * 2, 1);
	}
}
