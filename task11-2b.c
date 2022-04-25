#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main(void)
{
    int msqid;
    char pathname[] = "task11-2a.c";
    key_t key;
    int len, maxlen;

    struct mymsgbuf
    {
        long mtype;
        char mtext[81];
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

len = 81;

    for (int i = 1; i <= 5; i++)
    {

        // Блокируем текущий поток, пока не получим сообщение из второй программы.
        if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, len, 1, 0)) < 0)
        {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        printf("second program recived text: %s\n", mybuf.mtext);

        mybuf.mtype = 2;
        strcpy(mybuf.mtext, "This is text from second program");
        

        if (msgsnd(msqid, (struct msgbuf *)&mybuf, len, 0) < 0)
        {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(-1);
        }
    }

    return 0;
}
