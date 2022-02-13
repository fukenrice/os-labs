#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == -1) {
        printf("Error");
    } else if (pid == 0) {
        execv("task3-3.out", argv);
    } else {
        printf("Parent");
    }
}
