#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("argv: ");
    for (int i = 0; i < argc; ++i) {
        printf("%s ", argv[i]);
    }
    printf("envp: ");
    int i = 0;
    while (envp[i] != NULL) {
        printf("%s ", argv[i++]);
    }
}
