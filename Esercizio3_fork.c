#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Errore nella creazione del figlio.\n");
        return 1;
    }

    if (pid == 0) {
        // Processo Padre
        printf("[Padre] PID: %d\n", getpid());

        pid_t nipote = fork();

        if (nipote < 0) {
            printf("Errore nella creazione del nipote.\n");
            exit(1);
        }

        if (nipote == 0) {
            // Processo Nipote
            printf("[Nipote] PID: %d, PPID: %d\n",
                   getpid(), getppid());

            printf("[Nipote] Termino.\n");
            exit(0);
        } else {
            // Il padre attende il nipote
            wait(NULL);

            printf("[Padre] Il nipote ha terminato. Termino.\n");
            exit(0);
        }

    } else {
        // Processo Nonno
        printf("[Nonno] PID: %d\n", getpid());

        wait(NULL);

        printf("[Nonno] Il figlio ha terminato. Termino.\n");
    }

    return 0;
}