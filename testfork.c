#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int funcion() {
	long l;
	double x;
	for(l = 0; l < 2e9; l++) {
		x = sin(l) + x;
	}
}

int main() {
	time_t now = time(0);

	pid_t pid;
	printf("Proceso padre\n");
	pid = fork();
	if(pid<0) {
		perror("!....");
		exit(-1);
	} else if (pid == 0) {
		printf("\t> %d Soy el hijo\n", getpid());
		funcion();
	} else {
		printf("\n- %d Soy tu padre\n", getpid());
		funcion();
	}

	FILE *f;

	now = time(0) - now;

	f = fopen("time1.txt", "w+");
	fwrite(&now, sizeof(now), 1, f);
	fclose(f);
	printf("Time: %li", now);
}
