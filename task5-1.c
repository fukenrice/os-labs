#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int     fd;
  char    buffer[1];

  (void)umask(0);

  if ((fd = open("myfile.txt", O_RDONLY, 0666)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  while (read(fd, buffer, 1) > 0) {
    printf("%c", buffer[0]);
  }

  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }

  return 0;
}
