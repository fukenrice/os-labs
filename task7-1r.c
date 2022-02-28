#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
  int     fd;
  char     *array;    // Pointer to shared memory
  int     shmid;     // IPC descriptor for the shared memory
  char    pathname[] = "task7-1w1.c"; // The file name used to generate the key.
                                  // A file with this name must exist in the current directory.
  key_t   key;       // IPC key
  
  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, 8000*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
        if ((shmid = shmget(key, 8000*sizeof(char), 0)) < 0) {
            printf("Can\'t find shared memory0\n");
            exit(-1);
        }
    }
  }
  if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("Can't attach shared memory1\n");
    exit(-1);
  }
  for(int i = 0; i < 8000; ++i) {
        printf("%c", array[i]);
  }
    

  if (shmdt(array) < 0) {
    printf("Can't detach shared memory2\n");
    exit(-1);
  }
  shmctl(shmid, SHM_INFO, NULL);
  return 0;
}
