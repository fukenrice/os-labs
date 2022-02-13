#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        printf("Error");
    } else if (pid == 0) {
        printf("Child");
    } else {
        printf("Parent");
    }
}
