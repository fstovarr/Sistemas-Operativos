#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

double calc(unsigned long start, unsigned long end, int parent) {
    double res = 0;
    int counter = 0;

    for(unsigned long i = 0; i < end - start; i+=2) {
        double d = (4.0 / start);
        start += 2;

        if(counter++ % 2 == 0) {
            res = res + d;
        } else {
            res = res - d;
        }
    }

    return res;
}


int main() {
	pid_t pid;
	int pipefd[2];
	int r = pipe(pipefd);
	double buffer;

	if(r == -1) exit(-1);

	pid = fork();

	if(pid < 0) {
		perror("ERROR :(");
		exit(-1);
	} else if (pid == 0) {
		printf("[%d] Child started...\n", getpid());
		double res = calc(1L, 1e10L, 0);

		close(pipefd[0]);
		r = write(pipefd[1], &res, sizeof(double));
		close(pipefd[1]);
        printf("Child finished.\n");

	} else {
	    printf("[%d] Parent started...\n", getpid());
	    double res = calc(1e10L + 1, 1e19L, 1);

	    printf("Parent calc %.20f",res);

		close(pipefd[1]);
        r = read(pipefd[0], &buffer, sizeof(double));
        close(pipefd[0]);

        res += buffer;
        printf("%.20f\n", res, buffer);
        printf("Parent finished.\n");
	}
}
