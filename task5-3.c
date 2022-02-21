#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
  int fd[2];
  size_t size = 0;
  pipe(fd);
  fcntl(fd[1], F_SETFL, O_NONBLOCK);
  while (write(fd[1], "a", 1) == 1) {
      size++;
  }
  printf("%ld\n", size);
  return 0;
}
