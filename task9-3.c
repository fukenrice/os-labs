// Изначально инициализируем семафор нулевым значением. Так как родительский процесс должен отрабатывать сначала, логика работы будет следующая:
// Родитель:
// А(S, 2) - увеличиваем семафор на 2, чтобы вдальнейшем выполнить блок кода, не продолжная родительский поток
// write - передаем сообщение ребенку
// Z(2) - ждем, пока дочерний процесс выполнит свою работу
// read - читаем, что передал ребенок
// Ребенок:
// D(S, 1) - пока значение семафора 0(работает родитель) блокируем выполнение. Потом уменьшаем на единичку и выполняем код, связанный с pipe
// read - читаем что передал родитель
// write - передаем сообщение родителю
// D(S, 1) - выполнив весь код вычитаем единичку, и начинает работать родитель
// Соответственно все эти операции происходят в общем цикле до N




#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main()
{
    int fd[2], result;

    size_t size;
    char resstring[17];
    int shmid;
    int semid;
    struct sembuf mybuf;
    key_t key;
    char pathname[] = "task9-3.c";
    int N;

    printf("Please enter num of iterations: ");

    scanf("%d", &N);
    
    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if (pipe(fd) < 0)
    {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }

    result = fork();

    if (result < 0)
    {
        printf("Can\'t fork child\n");
        exit(-1);
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {

            if (result > 0)
            {
                /* Parent process */
                size = write(fd[1], "Hello, world!(P)", 17);

                if (size != 17)
                {
                    printf("Can\'t write all string to pipe\n");
                    exit(-1);
                }

                mybuf.sem_num = 0;
                mybuf.sem_op = 2;
                mybuf.sem_flg = 0;

                if (semop(semid, &mybuf, 1) < 0)
                {
                    printf("Can\'t add 2 to semaphore\n");
                    exit(-1);
                }

                mybuf.sem_num = 0;
                mybuf.sem_op = 0;
                mybuf.sem_flg = 0;

                if (semop(semid, &mybuf, 1) < 0)
                {
                    printf("Error waiting for zero\n");
                    exit(-1);
                }

                size = read(fd[0], resstring, 17);

                if (size != 17)
                {
                    printf("Can\'t read string from pipe\n");
                    exit(-1);
                }
                else
                {
                    printf("Parent read: %s\n", resstring);
                }

                printf("Parent goes to next iteration\n");
            }
            else
            {

                mybuf.sem_num = 0;
                mybuf.sem_op = -1;
                mybuf.sem_flg = 0;

                if (semop(semid, &mybuf, 1) < 0)
                {
                    printf("Error decreasing semaphore\n");
                    exit(-1);
                }

                size = read(fd[0], resstring, 17);

                if (size != 17)
                {
                    printf("Can\'t read string from pipe\n");
                    exit(-1);
                }

                printf("Child read: %s\n", resstring);

                size = write(fd[1], "Hello, world!(C)", 17);
                if (size != 17)
                {
                    printf("Can\'t write all string to pipe\n");
                    exit(-1);
                }

                mybuf.sem_num = 0;
                mybuf.sem_op = -1;
                mybuf.sem_flg = 0;
                if (semop(semid, &mybuf, 1) < 0)
                {
                    printf("Error decreasing semaphore\n");
                    exit(-1);
                }
                printf("Child goes to next iteration\n");
            }
        }
    }

    return 0;
}
