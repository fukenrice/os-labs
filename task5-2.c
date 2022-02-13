#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  // Creating two buffers: for parent and for child.
  int     fd_parent[2], fd_child[2], result;
  size_t size_write, size_read;
  // Creating two result strings.
  char  resstring_child[17], resstring_parent[16];
  // Opening two pipes child-panet and parent-child.
  if (pipe(fd_parent) < 0 || pipe(fd_child) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {

   /* Parent process */
    // Closing parents' reading side of pipe.
    if (close(fd_parent[0]) < 0) {
      printf("parent: Can\'t close reading side of pipe\n"); exit(-1);
    }

    size_write = write(fd_parent[1], "Parents' message", 17);

    // Closing childs' writing side of pipe.
    if (close(fd_child[1] < 0)) {
        printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
    }
    // Reading message from childs' pipe.
    size_read = read(fd_child[0], resstring_child, 17);
    if (size_read < 0) {
        printf("Can\'t read string from pipe\n");
        exit(-1);
    }

    if (size_write != 17) {
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }
    // Closing parents' reading side of pipe.
    if (close(fd_parent[1]) < 0) {
      printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
    }
    printf("Parent got resstring:%s\n", resstring_child);

    printf("Parent exit\n");

  } else {

    if (close(fd_child[0]) < 0) {
      printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }

    size_write = write(fd_child[1], "Childs' message", 16);

    if (close(fd_parent[1] < 0)) {
        printf("child: Can\'t close writing side of pipe\n"); exit(-1);
    }

    size_read = read(fd_parent[0], resstring_parent, 16);
    if (size_read < 0) {
        printf("Can\'t read string from pipe\n");
        exit(-1);
    }

    if (size_write != 16) {
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }

    if (close(fd_child[1]) < 0) {
      printf("child: Can\'t close writing side of pipe\n"); exit(-1);
    }
    printf("Child got resstring:%s\n", resstring_parent);

    printf("Child exit\n");
   }

  return 0;
}
