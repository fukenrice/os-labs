#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    // Creating folder for files.
    const char *folder = "/files";
    system("mkdir files");
    chdir("./files");

    int fd;
    char *filename = "1.txt";

    // Creating file.
    if ((fd = open(filename, O_CREAT, S_IREAD | S_IWRITE)) == -1) {
        printf("Can\'t create file\n");
        exit(-1);
    }

    // Closing file.
    if (close(fd) < 0) {
        printf("Can\'t close file\n");
        exit(-1);
    }

    // Filenames.
    char *file = malloc(1000);
    char *link = malloc(1000);
    int depth = 1;

    while (1) {
        // Saving filenames.
        sprintf(file, "%d.txt", depth);
        sprintf(link, "%d.txt", depth + 1);

        // Creating soft link.
        if (symlink(file, link) == 0) {
            // Opening file by link.
            if ((fd = open(link, O_RDONLY)) < 0) {
                printf("Recursion depth: %d\n", depth - 1);
                return 0;
            }
            // Closing file.
            if (close(fd) < 0) {
                printf("Can\'t close link %s!\n", link);
                exit(-1);
            }
        } else {
            printf("Can\'t create link for file %s\n", file);
            exit(-1);
        }
        depth++;
    }

    return 0;
}
