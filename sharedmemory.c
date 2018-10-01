#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


int main() {
    key_t key = 1234;
    pid_t pid;
    int shmId, r;
    float *ap;

    shmId = shmget(key, sizeof(float), IPC_CREAT | 0666);

    ap = shmat(shmId, 0, 0);

    pid = fork();

    if(pid == 0) {
        //cout << "Hijo";
        *ap = 3.14151617;
    } else {
        //cout << "Padre";
        printf("%f", *ap);
    }

    r = shmdt(shmId);
}
