#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static void sighandler(int signo) {
    if (signo == SIGUSR1) {
        printf("Parent PID: %d\n", getppid());
    } else if (signo == SIGINT) {
        int straw = open("list.txt", O_CREAT | O_APPEND | O_RDWR, 0666);
        if (errno != 0) {
            printf("ERROR %d: %s\n", errno, strerror(errno));
            exit(1);
        }
        char err[500];
        sprintf(err, "The process with PID %d has exited due to SIGINT\n",getpid());
        write(straw, err, 500);

        close(straw);
        exit(1);
    }
}

int main() {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);

    while(1) {
        printf("Current PID: %d\n", getpid());
        sleep(1);
    }
}
